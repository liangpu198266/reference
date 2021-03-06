/*
 * Copyright (C) sunny liang
 * Copyright (C) mini net cmd
 */
#include "fileUtils.h"

static int8 currentWorkPath[BUFSIZE];

int8 initFileDir(void)
{
  int32 rv = 0;
  
  memset(currentWorkPath, 0x0, BUFSIZE);

  if (getcwd(currentWorkPath,BUFSIZE) == FALSE)
  {
    return TASK_ERROR;
  }
  
  return TASK_OK;
}

int8 *getcurrentWorkPath(void)
{
  return currentWorkPath;
}
