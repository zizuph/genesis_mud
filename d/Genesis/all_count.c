#include <files.h>
#include <stdproperties.h>
    
#define TODO  "/d/Genesis/ALL_TODO"
#define FOUND "/d/Genesis/ALL_FOUND"
#define LEFT  "/d/Genesis/ALL_LEFT"
#define LOOP  5
#define OWNER "mercade"
    
#define TELL(message) tell_object(find_player(OWNER), (message)) 
    
private int processed = 1;
private int found;
    
public string
query()
{
    return "Processed " + processed + ", found " + found + ".\n";
}
    
private string
query_type(object obj)
{
    string fun = function_exists("create_object", obj);
    
    switch(fun)
    {
    case ARMOUR_OBJECT:
        return "armour    ";
    case WEAPON_OBJECT:
        return "weapon    ";
    case CONTAINER_OBJECT:
        fun = function_exists("create_container", obj);
        switch(fun)
        {
        case ROOM_OBJECT:
            return "room      ";
        case LIVING_OBJECT:
            return "living    ";
        default:
            return "container ";
        }
    case HEAP_OBJECT:
        fun = function_exists("create_heap", obj);
        switch(fun)
        {
        case FOOD_OBJECT:
            return "food      ";
        case DRINK_OBJECT:
            return "drink     ";
        case COINS_OBJECT:
            return "coin      ";
        default:
            return "heap      ";
        }   
    case POISON_OBJECT:
        return "poison    ";
    case HERB_OBJECT:
        return "herb      ";
    case DOOR_OBJECT:
        return "door      ";
    case KEY_OBJECT:
        return "key       ";
    case TORCH_OBJECT:
        return "torch     ";
    default:
        return "other     ";
    }
}
    
private void
process()
{
    string text;
    string text_found = "";
    string text_left = "";
    string *lines;
    int index;
    int size;
    object obj;
    int loaded;
    
    text = read_file(TODO, processed, LOOP);
    if (!strlen(text))
    {
	TELL("Done. " + query());
	destruct();    
    }
    
    lines = explode(text, "\n");
    size = sizeof(lines);
    index = -1;
    while(++index < size)
    {
    	if (!objectp(obj = find_object(lines[index])))
	{
	    catch(lines[index]->teleledningsanka());
	    obj = find_object(lines[index]);
    	    loaded = 1;
	}
	else
	{
	    loaded = 0;
	}

	if (objectp(obj))
    	{
    	    found++;
    	    text_found += query_type(obj) + lines[index] + "\n";

	    if (loaded)
	    {
		catch(obj->remove_object());

		if (objectp(obj))
		{
		    SECURITY->do_debug("destroy", obj);
		}
	    }
    	}
    	else
    	{
    	    text_left += lines[index] + "\n";
    	}
    }
    
    write_file(FOUND, text_found);
    write_file(LEFT, text_left);
    
    processed += size;
    
    set_alarm(1.0, 0.0, process);
}
    
public string
start()
{
    if (geteuid(previous_object()) != OWNER)
    {
    	return "Not owner.\n";
    }
    
    setuid();
    seteuid(getuid());
    
    set_alarm(1.0, 0.0, process);
    
    return "Process started.\n";
}
