#include <linux/init.h>
#include <linux/module.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("sunny liang");
MODULE_DESCRIPTION("procfs test module.");
MODULE_LICENSE("GPL");

#define PROCNAME "mytest"
static struct proc_dir_entry * myproc_entry = NULL;
static char msg[512]={0};
static int my_file_read(struct file * file,char *data,size_t len,loff_t *off)
{
        if(*off> 0)
                return 0;
        if(copy_to_user(data,msg,strlen(msg)))
                return -EFAULT;
        *off+= strlen(msg);
        return strlen(msg);
}

static int my_file_write(struct file *file, const char*data,size_t len,loff_t*off)
{

        if(copy_from_user(msg,(void*)data,len))
                return -EFAULT;
        msg[len]='\0';
        return len;
}

static struct file_operations my_file_test_ops={
       .read= my_file_read,
       .write= my_file_write,
};

static int __init procTest_init(void)
{
        //myproc_entry = create_proc_entry(PROCNAME,0666,NULL);//old
        myproc_entry = proc_create(PROCNAME,S_IRUGO | S_IFREG, NULL, &my_file_test_ops);//new
        if(!myproc_entry){
                printk(KERN_ERR"can't create /proc/mytest \n");
                return -EFAULT;
        }

        //myproc_entry->proc_fops=&my_file_test_ops;//old

        return 0;
}

static void __exit procTest_exit(void)
{
    remove_proc_entry(PROCNAME,NULL);
}

module_init(procTest_init);
module_exit(procTest_exit);

