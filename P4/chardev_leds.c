/*
 *  chardev_led.c: Creates a char device that shows led secuences
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for copy_to_user */
#include <asm/io.h>

typedef unsigned char uchar_t;

/*  
 *  Prototypes 
 */
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "led"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */

/* 
 * Global variables are declared as static, so are global within the file. 
 */

static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open?  
				 * Used to prevent multiple access to device */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;		/* This will be initialized every time the 
				   device is opened successfully */ 
//static int counter=0;		/* Tracks the number of times the character
//				 * device has been opened */

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{
        Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}

	printk(KERN_INFO "Soy un led muy majo\n");
	printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'sudo mknod -m 666 /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
	printk(KERN_INFO "Ahora no soy ni led ni majo.\n");
	/* 
	 * Unregister the device 
	 */
	unregister_chrdev(Major, DEVICE_NAME);
}

/* 
 * Called when a process tries to open the device file, like
 * "cat /dev/chardev"
 */
static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Open)
		return -EBUSY;

	Device_Open++;

	/* Initialize msg */
	//sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	sprintf(msg, "Hola marinero!\n");

	/* Initially, this points to the beginning of the message */
	msg_Ptr = msg;

	/* Increase the module's reference counter */
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/* 
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;		/* We're now ready for our next caller */

	/* 
	 * Decrement the usage count, or else once you opened the file, you'll
	 * never get get rid of the module. 
	 */
	module_put(THIS_MODULE);

	return 0;
}

/* 
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	/*
	 * Number of bytes actually written to the buffer 
	 */
	int bytes_to_read = length;

	/*
	 * If we're at the end of the message, 
	 * return 0 -> end of file 
	 */
	if (*msg_Ptr == 0)
		return 0;

	/* Make sure we don't read more chars than 
	 * those remaining to read
    	 */
	if (bytes_to_read > strlen(msg_Ptr))
		bytes_to_read=strlen(msg_Ptr);
			
	/* 
	 * Actually transfer the data onto the userspace buffer. 
	 * For this task we use copy_to_user() due to security issues 
	 */
	if (copy_to_user(buffer,msg_Ptr,bytes_to_read))
		return -EFAULT;

	/* Update the pointer for the next read operation */	
	msg_Ptr+=bytes_to_read;	
	
	/* 
	 * The read operation returns the actual number of bytes 
	 * we copied  in the user's buffer
	 */
	return bytes_to_read;
}

void setleds(uchar_t st){
	int retries=5;
	unsigned long timeout=1000;
	outb(0xED, 0x60);	//"despierta" teclado
	udelay(timeout);
	
	while (retries>0 && inb(0x60)!=0xfa) { // esperamos al controlador
		retries--;
		udelay(timeout);
	}
	
	if (retries!=0) { // comprobamos que el teclado esta listo
		outb(st,0x60);
	}

}

/*  
 * Called when a process writes to dev file: echo "hi" > /dev/chardev 
 */
static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	//printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	
	//unsigned long copy_from_user (void * to, const void __user * from, unsigned long n);
	int i=0;
	uchar_t state=0b0;
	char input[4];
	if(copy_from_user(&input, buff, len)){
		return -EINVAL;
	}
	while(i<len){
		if(input[i]=='3'){//scroll
			state |= 0b1;
		}
		if(input[i]=='2'){//caps
			state |= 0b100;
		}
		if(input[i]=='1'){//bolq.num
			state |= 0b10;
		}
		if(input[i]=='0'){//0
			state |= 0b0;
		}
		i++;
	}
	setleds(state);
	return len;
}










