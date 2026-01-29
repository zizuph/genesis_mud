/*
 * /d/Gondor/common/battle/battle.c
 *
 * The base room for setting up a battle.
 * An example battle room:
 * 
 * inherit "/d/Gondor/common/battle/battle.c";
 * #include "battle.h"
 *
 * void
 * create_battle()
 * {
 *     set_battle_name("plains-skirmish");
 *
 *     add_room("/d/Gondor/rohan/plains/i09.c", 
 *         ({ 1, "uruk.c", 3, "hilltroll", 4, "orc.c"}) );
 *     add_room("/d/Gondor/rohan/plains/i10.c", 
 *         ({ 5, "uruk.c", 12, "orc.c" }) );
 *
 *     set_rq_stage(RQ_LEFT_LOTHLORIEN);
 *     set_extra_time(random(720));
 * }
 *
 * To do something to each npc as it is sent to battle, mask npc_extras().
 * To do something when the battle starts, mask battle_function().
 * Coded by Gwyneth, June 24, 2001
 */
inherit "/d/Gondor/common/room";
#include "/d/Gondor/common/battle/battle.h"
#include "/d/Gondor/defs.h"

int     gRQStage  = RQ_GANDALF_IN_BAGEND;
int     gExtra    = 0;
mapping gRooms    = ([]);
mixed   gRestrain = "";
string  gName     = "";
object  *gNpcs    = ({});

void     add_room(string path, mixed npcs);
void     set_battle_name(string name);
void     set_extra_time(int extra);
void     set_restrain_path(mixed path);
void     set_rq_stage(int stage);
int      query_extra_time();
int      query_rq_stage();
mixed    query_restrain_path();
string   query_battle_name();
string * query_room();

void
create_battle()
{
}

void
create_room()
{
    set_short("battle setup room");
    set_long("This is a battle setup room.\n");
    create_battle();
}

/*
 * Function name: battle_function
 * Description  : Define this yourself to call your own function when the
 *                battle starts.
 */
int
battle_function()
{
    return 0;
}

/*
 * Function name: npc_extras
 * Description  : Do stuff to each npc before they get sent to battle
 *                if needed.
 * Arguments    : object npc - The npc to deal with
 */
int
npc_extras(object npc)
{
    return 0;
}

void
set_rq_stage(int stage)
{
    gRQStage = stage;
}

int
query_rq_stage()
{
    return gRQStage;
}

void
set_restrain_path(mixed path)
{
    gRestrain = path;
}

string
query_restrain_path()
{
    return gRestrain;
}

void
set_extra_time(int extra)
{
    gExtra = extra;
}

int
query_extra_time()
{
    return gExtra;
}

void
set_battle_name(string name)
{
    gName = name;
}

string
query_battle_name()
{
    return gName;
}

void
add_room(string path, mixed npcs)
{
    int i, size;

    for (i = 1, size = sizeof(npcs); i < size; i += 2)
    {
        if (file_size(BATTLE_NPC_DIR + npcs[i] + ".c"))
        {
            npcs[i] = BATTLE_NPC_DIR + npcs[i] + ".c";
        }

        if (extract(npcs[i], 0, 0) != "/")
            npcs[i] = "/" + npcs[i];
        if (extract(npcs[i], -2, -1) != ".c")
            npcs[i] += ".c";

        if (member_array(path, m_indexes(gRooms)) == -1)
        {
            gRooms += ([ path : ({ npcs[i - 1], npcs[i] }) ]);
        }
        else
        {
            gRooms[path] += ({ npcs[i - 1], npcs[i] });
        }
    }
}

mapping
query_room()
{
    return gRooms;
}

void
start_battle()
{
   int i, size, j, jsize, k, ksize;
   string *rooms = m_indexes(gRooms); // List of rooms

   for (i = 0, size = sizeof(rooms); i < size; i++)
   {
       /* Load each room */
       catch(rooms[i]->teleledningsanka());

       /* Does the room exist? */
       if (objectp(find_object(rooms[i])))
       {
           /* The list of npc pathnames */
           for (j = 1, jsize = sizeof(gRooms[rooms[i]]); j < jsize; j += 2)
           {
               /* The number of npcs to clone */
               for (k = 0, ksize = gRooms[rooms[i]][j - 1]; k < ksize; k++)
                   gNpcs += ({ clone_object(gRooms[rooms[i]][j]) });
           }
       }

       gNpcs = filter(gNpcs, objectp);

       gNpcs[0]->set_team_leader();

       /* Move each cloned npc and arm them. */
       for (j = 0, jsize = sizeof(gNpcs); j < jsize; j++)
       {
           if (strlen(gRestrain))
               gNpcs[j]->set_restrain_path(gRestrain);

           npc_extras(gNpcs[j]);
           gNpcs[j]->arm_me();
           gNpcs[j]->move_living("somewhere", rooms[i], 1, 1);
	   if (j > 0)
               gNpcs[0]->team_join(gNpcs[j]);
       }
   }

   /* Call any unique function that is indicated */
   battle_function();
}

void
start_battle_alarm()
{
    set_alarm(itof(gExtra), 0.0, start_battle);
}

void
notify_clock()
{
    CLOCK->notify_rq_stage(start_battle_alarm, gRQStage);
}
