#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/fs.h>
#include <unistd.h> 
#include <sys/types.h>
#include <ext2fs/ext2_fs.h>
//#include "ext2_fs.h"

int main(int argc, char *argv[]){

	int fd;
	int count;
	int ino, i;
	int bgno, iindex, inode_size, block_size;
	int arr[1024];
	
	unsigned long inode_offset;
	struct ext2_super_block sb;
	struct ext2_inode inode;
	struct ext2_group_desc bgdesc;
	
	
	
	ino = atoi(argv[2]);
	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("readsuper:");
		exit(errno);
	}
		
	lseek64(fd, 1024, SEEK_CUR);	
	printf("size of upper block = %lu\n", sizeof(struct ext2_super_block));
	
	count = read(fd, &sb, sizeof(struct ext2_super_block));
	printf("Magic: %x\n", sb.s_magic);
	printf("Inodes Count: %d\n" , sb.s_inodes_count);
	printf("size of BG DESC = %lu\n", sizeof(struct ext2_group_desc));
	
	inode_size = sb.s_inode_size;
	block_size = 1024 << sb.s_log_block_size;
	
	bgno = (ino -1)/sb.s_inodes_per_group;
	iindex = (ino -1) % sb.s_inodes_per_group;
	lseek64(fd, 1024 + block_size + bgno * sizeof(bgdesc), SEEK_SET);
	count = read(fd, &bgdesc, sizeof(struct ext2_group_desc));
	printf("Inode Table: %d\n",bgdesc.bg_inode_table);
	
	inode_offset = bgdesc.bg_inode_table * block_size + iindex * inode_size;
	
	lseek64(fd, inode_offset, SEEK_SET);
	read(fd, &inode, sizeof(inode));
	printf("size of file %d \n", inode.i_size);
	printf("number of blocks %d, blocks: ",inode.i_blocks);
	
	for(i = 0; i < 12; i++)
        	printf("%d,", inode.i_block[i]);
	
	int arr2[block_size/4];
	lseek64(fd, inode.i_block[12]*block_size, SEEK_SET);
	read(fd, &arr2, block_size);
	printf("%d,",inode.i_block[12]);
	for(i = 0; i < block_size/4; i++){
	if(arr2[i]==0){break;}
        	printf("%d,", arr2[i]);
        }
        	
        int arr3[block_size/4];
        int arr4[block_size/4];
	lseek64(fd, inode.i_block[13]*block_size, SEEK_SET);
	read(fd, &arr3, block_size);
	
	for(i = 0; i < block_size/2; i++)
	{
	       
	       if(arr3[i]==0){break;}
	      //int arr2[block_size/4];
	lseek64(fd, arr3[i]*block_size, SEEK_SET);
	read(fd, &arr4, block_size);
	//printf("%d,",inode.i_block[12]);
	for(int j = 0; j < block_size/4; j++){
		if(arr4[j]==0){ break;}
	         
        	printf("%d,", arr4[j]);
        	}
        }
        
        //start of TIND
        
        int arr5[block_size/4];
        int arr6[block_size/4];
        int arr7[block_size/4];
	lseek64(fd, inode.i_block[14]*block_size, SEEK_SET);
	read(fd, &arr5, block_size);
	
	for(int k = 0; k < block_size/4; k++)
	{
	       
	       if(arr5[k]==0){break;}
	      //int arr2[block_size/4];
	lseek64(fd, arr5[k]*block_size, SEEK_SET);
	read(fd, &arr6, block_size);
	for(i = 0; i < block_size/4; i++)
	{
	       
	       if(arr6[i]==0){break;}
	      //int arr2[block_size/4];
	lseek64(fd, arr6[i]*block_size, SEEK_SET);
	read(fd, &arr7, block_size);
	//printf("%d,",inode.i_block[12]);
	for(int j = 0; j < block_size/4; j++){
		if(arr7[j]==0){ break;}
	         
        	printf("%d ,", arr7[j]);
        	}
        }
        
        }
	
	  
	
	close(fd);}
