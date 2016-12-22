/*
 * Copyright (C) sunny liang
 * Copyright (C) mini net cmd
 */

#ifndef __SIGNALEX_H__
#define __SIGNALEX_H__

#include "common.h"

typedef enum
{
  SIGNAL_DISABLE = 0,
  SIGNAL_ENABLE
}sigNodeStatus_t;

typedef enum
{
  SIG_NODE_STATIC = 0,
  SIG_NODE_ACTIVE
}sigNodeType_t;


#define   COMM_RESTART             0x10      //restart
#define   COMM_DISPLAY_SERVER      0x12      //display service info

#define   MININET_SIGNAL_SIGINT                 SIGINT
#define   MININET_SIGNAL_SIGQUIT                SIGQUIT
#define   MININET_SIGNAL_SIGCHLD                SIGCHLD
#define   MININET_SIGNAL_RESTART                COMM_RESTART
#define   MININET_SIGNAL_DISPLAY_SERVER         COMM_DISPLAY_SERVER


typedef struct signalNode_ 
{
  int32                   sigNo; 
  int8                    *sigName;
  int8                    (*signalHandler)(int32 sig); 
  sigNodeStatus_t         flag;
  sigNodeType_t           nodeType;
}signalNode_t;

int32 sigPoolInit(void);
int8 addNewSignalNode(signalNode_t *node);
int32 sigPoolFree(void);
int8 unblockProcSig(sigset_t *set);
int8 blockProcSig(sigset_t *set);


#endif

