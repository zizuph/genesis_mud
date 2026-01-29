inherit "/std/object";
#include <spguild.h>
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
 
void create_object()
{
    set_short("joiner");
    set_long("Joiner to Spiders.\n");
    set_name("joiner");
}
 
void init()
{
    add_action("join","join");
    ::init();
}
 
int join(string param)
{
    string *souls;
    int i;
    int joined;
 
    setuid();
    seteuid(getuid());
    NF("Join where? Spiders?\n");
    if (param!="spiders") return 0;
    souls=TP->query_cmdsoul_list();
    joined=0;
    for (i=0;i<sizeof(souls);i++)
        if (souls[i]==GUILDDIR+"spsoul.c") joined=1;
    if (joined)
      {
        write("You already joined Spiders!\n");
        return 1;
      }
    if (TP->add_cmdsoul(GUILDDIR+"spsoul.c"))
      {
        write("Congratulations! You have joined the Spiders!\n");
        TP->update_hooks();
        return 1;
      }
    else
      {
        write("Aaaarrrrrggggghhhhhh.... Something wrong :(\n");
        return 1;
      }
}
