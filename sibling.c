#include <linux/printk.h>
#include <linux/syscalls.h>

int _getsiblings(pid_t pid, pid_t __user* pidbuf, int cap)
{
	int index = 0;
	pid_t cpid;
	struct task_struct* parent, child;
	struct list_head* list;
	
	if (pid == 0)
	{
		cpid = get_current()->pid;
		parent= get_current()->real_parent;
	}
	else
	{
		cpid = pid;
		int CUID = get_current()->cred->uid.val;
		int AUID = find_task_by_vpid(pid)->cred->uid.val;

		if(CUID != AUID)
		{
			return -EPERM;
		}

		parent = find_task_by_vpid(pid)->real_parent;
	}

//	printk("PID %d\n", cpid);
//	printk("PPID %d\n", parent->pid);
//	printk("cap %d \n", cap);

	list_for_each(list, &parent->children)
	{
		child = list_entry(list, struct task_struct, sibling);

//		printk("SPID: %d\n", child->pid);

		if(child->pid == cpid)
			continue;
			
		if(index + 1 >= cap)
			break;

		pidbuf[index] = child->pid;
//		printk("index: %d\n", index);
		index++;
	}

	return index;
}

SYSCALL_DEFINE3(getsiblings, pid_t, pid, pid_t __user *, pidbuf, int, cap)
{
//	printk("getsiblings: %d %d", pid, cap);
	return _getsiblings(pid, pidbuf, cap);
}
