#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <wa_types.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>

#define TMP_OBJ  RMCVAR+"tmp"

static int rup = 0;
mixed *rdata = ({ });
string *richmembers;
int *richpaid;
int *humble;
int *richnews;
int howmuch;
int *accounts;
int *suspended;
int *m_note;
int *visible;
int *purchased;
int president, vicepres;

public void
create_room()
{
    seteuid(getuid(TO));

    set_short("The Rich Men's Club Control");
    set_long(break_string(
        "A small room with just a sign telling you to do 'rupdate'."+
        "\n",60));
  
    INSIDE;

    richmembers = ({});
    richpaid    = ({});
    accounts    = ({});
    m_note      = ({});
    humble      = ({});
    richnews    = ({});
    visible     = ({});
    suspended   = ({});
    purchased   = ({});

    restore_object(RICH_OBJ);
    
}

void
init()
{
    ::init();

    add_action("rupdate","rupdate");
}

int
rupdate()
{
    int i;

    if (!rup)
    {
        restore_object(RMCMASTER);

        for (i = 0; i < sizeof(richmembers); i++)
            rdata += (({ ({richmembers[i], richpaid[i], accounts[i],
                           m_note[i], humble[i], richnews[i], visible[i],
                           suspended[i], purchased[i] }) }));
        
        save_object(TMP_OBJ);
        rup = 1;
        write("Ok. tmp.o is updated.\n");
        return 1;
    }
    write("Already made...you'll have to update the room first.\n");
    return 1;
}
