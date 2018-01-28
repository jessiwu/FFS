#ifndef FFS_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

//#include "disk.h"


typedef struct fs_tree_node {
    uint8_t type;                       //type of node
    char *name;                         //name of node
    char *fullname;                     //full path of node
    
    struct fs_tree_node *parent;        //link to parent
    struct fs_tree_node **children;      //links to children
    uint32_t len;                       //number of children

    uint8_t *data;						//data for read and write
    uint64_t data_size;						//size of data
    uint64_t block_count;               // number of blocks
}fs_tree_node;

/*
types:
    1 = file
    2 = directory
*/

int destroy_node(fs_tree_node *node);        //free all parts a node from the FS tree
int init_fs();              //initialize FS tree with root
int dfs_dispatch(fs_tree_node *curr, int (*foo)(fs_tree_node *));   // apply a function to a node and its children recursively


fs_tree_node *node_exists(const char *path);        //check if node exists
fs_tree_node *add_fs_tree_node(const char *path, short type);     //add a node to FS tree at path
int remove_fs_tree_node(const char *path);          //remove a node from FS tree

#endif