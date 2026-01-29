/* A tiny routine to add new descriptions for modules to 
 * the module_desc.o file in the -/guild directory.
 * This object self-destruct after successfully upgrading the 
 * .o file.
 * Created by Dajala
 * Latest update: 23.05.1995
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/gnome/guild/new_desc.h"

/* Global variables */
string *module_desc;

/* Prototypes */
void upgrade();

void
create_object()
{
    set_name("upgrader");
    set_short("gnomish upgrader");
    set_adj("gnomish");
    set_long("Normally you shouldn't be able to read this since the "
        + "upgrader self-destructs after use.\n");
    set_alarm(1.0, -1.0, "upgrade");
    set_alarm(2.0, -1.0, "remove_object");
}

void
upgrade()
{
   string *buffer;
   int size, i;

   if(!strlen(NEW_DESC))
   {
       write("Create a file named:\n/d/Krynn/gnome/guild/new_desc.h\n"   
                + "defining a string named NEW_DESC first.\n");
       return;
   }
   
   seteuid(getuid());
   restore_object("/d/Krynn/gnome/guild/module_desc");
   size = sizeof(module_desc);
   write("Old size: " + size + "\n");
   buffer = allocate(size + 1);
   for(i=0;i<size;i++)
        buffer[i] = module_desc[i];
   buffer[size] = NEW_DESC;     /* Counting starts with 0 */
   module_desc = buffer;
   
   write("Ok, new description added.\n");
   seteuid(getuid());
   save_object("/d/Krynn/gnome/guild/module_desc_new");
   write("Ok, array saved with name 'module_desc_new.o'.\n");
   rm("/d/Krynn/gnome/guild/new_desc.h");
   write("Ok, new_desc.h removed.\n");
   return;
}

