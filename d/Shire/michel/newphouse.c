/* 1998/09/02 ? Previous update
 * 2011/03/27 Finwe - Added map
 * 2011/07/19 Lavellan - Added entry message in house and improved doorknocker.
 */

inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"


int do_knock(string str);

void
create_room()
{
     int i;
     string *herbs;
   add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 3;
   areadesc = "path";
 
   extraline = "You stand outside a small cottage just off the Fair road. "+
	     "It looks recently painted and you suppose that it must have "+
	     "a new occupant. Bushes and trees line your way back south, but "+
	     "in the other directions, you see nothing but green grass and "+
	     "bushes.";
    
    add_item(({"cottage","paint"}),
	     "The cottage is made of some sort of earthen material, all "+
	     "except for the door, which is round and wooden. The baked "+
	     "earthen material seems to have a fresh coat of whitewash, "+
	     "making it look pretty spiffy.\n");
    
    add_item(({"bushes","bush","trees","tree"}),
	     "The bushes and trees have grown so thickly together "+
	     "you have no way of telling what kind they are.\n");
    
    add_item(({"door"}), "The door is circular like a hobbit's should be, " +
	     "and even has a brass-looking doorknocker on it.\n");
    add_item(({"door knocker","doorknocker"}),
	     "The doorknocker is a plain brass maple leaf, " +
	     "attached to the door by a nail.\n");
    
    add_exit(MICH_DIR + "gamroad4", "west",0,1);    

    herbs = ({HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))],
       HERBS[random(sizeof(HERBS))]});
   
   for(i = 0; i < sizeof(herbs); i++)
   add_herb_file(herbs[i]);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_prop(OBJ_I_SEARCH_TIME,8);
   
   set_search_places(({"bushes","bush","tree","trees","ground","grass"}));
   
   make_the_room();
}

void
init()
{
    ::init();
    add_action("do_knock","knock");
}

/*
 * knock doorknocker? Too odd syntax.
 * Changed to use parse_command() by Sir Rogon. 
 * Also note that we must use notify_fail()
 * so that we do not disable a normal "knock"
 * command.
 */
int
do_knock(string str)
{
    notify_fail("Knock what?\n");

    if (!strlen(str))
        return 0; 

    if (!parse_command(str, ({}), "[on] [at] [the] [door] [with] [using] [the] 'doorknocker'")) 
    {
        write("Knock what? Maybe you should knock on the doorknocker?\n");
	    return 1;
    }
    
    write("You knock on the door with the doorknocker, and walk right in.\n");
    say(QCTNAME(TP) + " knocks on the door with a doorknocker.\n");
    say(QCTNAME(TP) + " walks into the cottage.\n");
    TP->move_living("M",MICH_DIR + "petunia_house",1);
    tell_room(MICH_DIR + "petunia_house", QCTNAME(TP) + " walks in.\n", TP);
    return 1;

    /*    if (!parse_command(str, ({}), "[on] [at] [the] [door] [with] [using] [the] 'doorknocker'")) 
    {
	    write("You knock " + str + " but nothing happens.\n");
    write("Maybe you should knock on the doorknocker?\n");
	    return 1;
    }
    
    write("You knock " + str + ", and walk right in.\n");
    say(QCTNAME(TP) + " knocks on the door with a doorknocker.\n");
    say(QCTNAME(TP) + " walks into the cottage.\n");
    TP->move_living("M",MICH_DIR + "petunia_house",1);
    return 1;*/
}

reset_room()
{
 set_searched(0);
}

