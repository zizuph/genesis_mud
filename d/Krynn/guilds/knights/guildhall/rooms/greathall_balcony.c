/* Balcony over Great Hall */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include "../../guild.h"

inherit IN_BASE;

#define     GM 		    ({VROOM + "grandmaster_office", VROOM + "void"})
#define     ROSE            ({VROOM + "kn5", VROOM + "void"})
#define     SWORD           ({VROOM + "kn4", VROOM + "void"})
#define     CROWN           ({VROOM + "kn3", VROOM + "void"})

string great_hall_desc();
string gm_desc();
object *keys = ({ 0,0,0,0,0,0 });
object key, gm_door, sw_door, ro_door, cr_door;
string gm;
string crown_desc();
string sword_desc();
string rose_desc();

void
reset_vin_room()
{
}

string door_desc()
{
    string str = "", tmp;

    if (objectp(cr_door) && !cr_door->query_open())
        str += "A bronze door. ";

    if (objectp(ro_door) && !ro_door->query_open())
        str += "A golden door. ";

    if (objectp(gm_door) && !gm_door->query_open())
	str += "A platinum door. ";

    if (objectp(sw_door) && !sw_door->query_open())
	str += "A silver door. ";

    if (strlen(str))
	tmp = "\n"+str+"";

    return tmp;
}

void
create_vin_room()
{
    (cr_door = clone_object(VOBJ + "crown_a"))->move(TO);
    (ro_door = clone_object(VOBJ + "rose_a"))->move(TO);
    (gm_door = clone_object(VOBJ + "gm_a"))->move(TO);
    (sw_door = clone_object(VOBJ + "sword_a"))->move(TO);

    set_short("Balcony overlooking the Great Hall");
    set_long("You stand on a balcony above the Great Hall of Vingaard Keep. "+
      "@@great_hall_desc@@ In the curving wall of this semi-circular room are "+
	"set four ornate doors leading to the offices of the Conclave. There are "+
	"two small, triangular shaped windows on "+
      "either side of the doors, allowing you to glimpse inside the office. "+
      "Stairs lead down towards the Great Hall to the southeast and southwest. @@door_desc@@\n");
    AI(({"window", "windows"}), "To look through the window, <view> a particular office. "+
      "You may also <seek conclave member/guildmaster> here.\n");

    add_prop(ROOM_I_LIGHT,2);

    AE(VROOM + "great_hall", "southeast", "@@down_stairs");
    AE(VROOM + "great_hall", "southwest", "@@down_stairs");

    reset_vin_room();
}
    
void 
init()
{
    ::init();
    add_action("do_view", "view");
    add_action("do_seek", "seek");
}

void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if ((ADMIN)->is_grandmaster(ob->query_name()) ||
	ADMIN->is_conclave(ob->query_name()))
	set_alarm(0.0, 0.0, "give_key", ob);
}

int 
do_view(string str)
{
    if (str == "crown" || str == "crown office" || str == "the crown office")
    {
        TP->catch_msg(crown_desc());
        return 1;
    }
    else if (str == "sword" || str == "sword office" || str == "the sword office")
    {
        TP->catch_msg(sword_desc());
        return 1;
    }
    else if (str == "rose" || str == "rose office" || str == "the rose office")
    {
        TP->catch_msg(rose_desc());
        return 1;
    }
    else if (str == "grandmaster" || str == "grandmaster office" || str == "the grandmaster office")
    {
	TP->catch_msg(gm_desc());
	return 1;
    }

    NF("View what? The crown|sword|rose|grandmaster office?\n");
    return 0;
}

public int
do_seek(string str)
{
    int i,succ;
    object gm;

    if (!str)
    {
        write("Seek an audience with which one? Seek crown, "+
            "sword, rose, grandmaster or guildmaster.\n"); 
    }
    if ((str == "crown") || (str == "an audience with crown") ||
	str == "high warrior" || str == "High Warrior") 
    {           
        if (find_player(L(ADMIN->query_conclave("crown"))))
        {
            write("The High Knight of the Crown Order now knows that "+
                "you seek an audience.\n"); 
            tell_object(find_player(L(ADMIN->query_conclave("crown"))),"\n     "+
                this_player()->query_name() + 
                " seeks an audience with you.\n\n");
            return 1;
        }
        write("The High Knight of the Crown is not where you seek. "+
            "Perhaps you should try again later?\n");   
        return 1;
    }

    if ((str == "sword") || (str == "an audience with sword") ||
	str == "high clerist" || str == "High Clerist")
    {
        if (find_player(L(ADMIN->query_conclave("sword"))))
        {
            write("The High Knight of the Sword now knows that you "+
                "seek an audience.\n");
            tell_object(find_player(L(ADMIN->query_conclave("sword"))),"\n     "+
                this_player()->query_name() + 
                " seeks an audience with you.\n\n");
            return 1;
        }
        write("The High Knight of the Sword is not where you seek. "+
            "Perhaps you should try again later?\n");
        return 1;
    }
    if ((str == "rose") || (str == "an audience with rose") ||
	str == "high justice" || str == "High Justice")
    {
        if (find_player(L(ADMIN->query_conclave("rose"))))
        {
            write("The High Knight of the Rose now knows that you "+
                "seek an audience.\n");
            tell_object(find_player(L(ADMIN->query_conclave("rose"))),"\n     "+
                this_player()->query_name() + 
                " seeks an audience with you.\n\n\n");
            return 1;
        }
        write("The High Knight of the Rose is not where you seek. "+
            "Perhaps you should try again later?\n");
        return 1;
    }
    if ((str == "guildmaster") || (str == "an audience with the guildmaster"))
    {
        succ=0;
        for(i=0;i<sizeof(GUILDMASTERS);i++)
        {
          gm = find_player(L(GUILDMASTERS[i]));
          if (gm && !(gm->query_prop(WIZARD_I_BUSY_LEVEL) & 156))
          {
            gm->catch_msg("\n******************\n"+
                        this_player()->query_name() + 
                        " seeks an audience with you.\n\n\n");
            succ=1;
          }
        }
        if (succ)
          write("Someone up there now knows that you seek an audience.\n");
        else
          write("There is currently no one up there to hear you. "+
                "Perhaps you should try again later?\n");
        return 1;
    }
    if ((str == "grandmaster") || (str == "an audience with grandmaster") ||
	str == "grand master" || str == "Grand Master")
    {
	if (find_player((ADMIN)->query_grandmaster()))
	{
	    write("The Grand Master of the Knighthood now knows that "+
	      "you seek an audience.\n");
	    tell_object(find_player((ADMIN)->query_grandmaster()), "\n     "+
	      this_player()->query_name() +
	      " seeks an audience with you in Vingaard Keep.\n\n");
	    return 1;
	}
	write("The Grand Master of the Knighthood is not where you seek. "+
	  "Perhaps you should try again later?\n");
	return 1;
    }

    write("If what you seek isn't a Knight conclave member or the Guild Master, "+
	"then you are seeking in the wrong place.\n");
    return 1;
}

void 
give_key(object ob)
{
    int lvl = ob->query_knight_level();
    string key_file;

    if (ADMIN->is_grandmaster(ob->query_name()) && !key)
    {
	key = clone_object(VOBJ + "gm_key");
	key->move(ob);
	ob->catch_msg("\nSuddenly, an ornate key appears in your hand!\n");
	return;
    }
    else if (ADMIN->is_grandmaster(ob->query_name()))
        return;

    if (lvl == 3)
      key_file = "crn_key";
    else if (lvl == 4)
      key_file = "swd_key";
    else if (lvl == 5)
      key_file = "rose_key";
    else
      return;
    seteuid(getuid());
    if (!keys[lvl] && ob && E(ob) == TO)
      {
          keys[lvl] = clone_object(VOBJ + key_file);
          keys[lvl]->move(ob);
     ob->catch_msg("\nSuddenly, an ornate key appears in your hand!\n");
      }
}

string
gm_desc()
{
    object *inv, *live;
    int i;

    (VROOM + "grandmaster_office")->load_me();
    inv = all_inventory(find_object(VROOM + "grandmaster_office"));

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	if (sizeof(live) > 0)
	    return ("In that room you can see " +
	      COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

string 
crown_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = CROWN;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

string 
sword_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = SWORD;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

string 
rose_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = ROSE;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

int
down_stairs()
{
    write("You walk down the stairway, descending into the Great Hall of "+
      "Vingaard Keep.\n");
    return 0;
}

string
great_hall_desc()
{
    object *inv, *live, *dead;
    int i;

    inv = all_inventory(find_object(VROOM + "great_hall"));

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	live -= ({ TP });
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	    return ("Looking out across the great hall, you see " +
	      COMPOSITE_LIVE(live) + ", as well as " +
	      COMPOSITE_DEAD(dead)+". ");
	else if (sizeof(live) > 0)
	    return ("Looking out across the great hall, you see " +
	      COMPOSITE_LIVE(live)+". ");
    }

    return ("The great hall is empty. ");
}
