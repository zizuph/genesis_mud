/*
 * tasker.c
 * 
 * By Skippern Dec 2000
 * 
 * Inherit this in all rooms/objects that completes tasks.
 * Use function complete_task(int task); to initialize the change.
 *
 * Examples used:
 * /d/Gondor/common/ship/pel_tours.c by Olorin
 *
 */
#pragma save_binary

#define TASK_ITEM            "Erech_Task_Item"

string complete_task(int task);

string
complete_task(int task)
{
    object  item,
            tp = this_player();

    item = present(TASK_ITEM, tp);

    if (!objectp(item))
    {
	return "";
    }
	
    if (item->query_task_no() != task)
    {
        return "";
    }

    if (item->query_task_done())
    {
	return "";
    }

    if (item->query_task_no() == task)
    {
	item->set_task_done();
	switch (task)
	{
	case 0:
	    write("You have sucsesfully found the cave, and " + 
		  "feel confidently that you can return to Utmir.\n");
	    break;
	case 1:
	    write("You have found the covenent rock of Erech, and know " +
		  "now where King Morthec swore the oath to Isildur.\n");
	    break;
	case 2:
	    write("Of course you know cats like fresh milk.\n");
	    break;
	case 3:
	    write("Task not completed by Skippern, so how can you complete " +
		  "it?\n");
	    break;
	default:
	    write("This quest doesn't exsist!\n");
	    break;
	}
	return "";
    }

    return "";
}

