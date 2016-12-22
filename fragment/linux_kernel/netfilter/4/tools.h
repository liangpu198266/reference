int inet_i2str(unsigned int addr,char *addr_str){
  unsigned char *p;
  int i;
  p=(unsigned char *)(&addr);
  for(i=0;i<4;i++){
     addr_str[i*4+0]=*(p+i)/100+'0';
     addr_str[i*4+1]=*(p+i)/10-(*(p+i)/100)*10+'0';
     addr_str[i*4+2]=*(p+i)%10+'0';
     addr_str[i*4+3]='.';
  }
  addr_str[15]='/0';
  return 0;
}
