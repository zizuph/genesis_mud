#include "/d/Shire/common/defs.h"
#include "/d/Shire/skills.h"
#include "trickster.h"
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#define CHECK_MAXIMUM(i)   (MAX(i, TASK_FORMIDABLE))
#define CHECK_MINIMUM(i)   (MIN(i,TASK_SIMPLE))


//  Prototypes
void set_up_snare(object rope, object trigger, object player);
void set_pit_trap(object shovel, object player, int size);
void set_up_slick(object flask, object player);
void set_up_tripwire(object wire,object player, string direction);
void set_up_bucket(object bucket,object door, object player);

int silent;
int trap_id;

object
paralyze(int time)
{
    object para;

    setuid(); seteuid(getuid());
    para = clone_object("/std/paralyze");
    para->set_standard_paralyze("trap");
    para->add_name("_trickster_paralyze");
    para->set_stop_fun("abandon_trap");
    para->set_stop_object(TO);
    para->set_stop_verb("stop");
    para->set_stop_message("You abandon making your trap!\n");
    para->set_fail_message("You can't do that since you are currently busy "+
      "setting up your trap.  Type 'stop' to quit setting it up.\n");
    para->set_remove_time(time);

    silent = 0;
    return para;
}

int
abandon_trap()
{
    remove_alarm(trap_id);
    trap_id = 0;
    if (!silent)
	say(QCTNAME(TP)+" abandons setting up "+HIS_HER(TP)+" trap.\n");
    return 0;
}

int
snaretrap(string str) 
{
    int time;
    object *trigger, rope, para;

    rope = present("rope",TP);
    //       Wizards don't need a rope!!
    if (!rope && !TP->query_wiz_level())
    {
	notify_fail("You need a rope of some sort to set up your "+
	  "snare trap!\n");
	return 0;
    }
    //  See if we have an object to trap
    trigger = FIND_STR_IN_OBJECT(str,ENV(TP));
    if (sizeof(trigger) != 1 || living(trigger[0]))
    {
	notify_fail("Set up a snare trap on what?\n");
	return 0;
    }
    //   Fail if the shadow is already in the object
    if (trigger[0]->query_trickster_shadow() == 666)
    {
	notify_fail("But the "+str+" has already been trapped, silly!!\n");
	return 0;
    }
    //   Make sure the object isn't already ungettable
    if (trigger[0]->query_prop(OBJ_M_NO_GET))
    {
	notify_fail("Why would you trap something which can not be taken?\n");
	return 0;
    }
    write("You grin evilly as you set up your snare trap on the "+
      trigger[0]->short()+", thinking of the poor fool that will wind up "+
      "springing your trap.\n");
    say(QCTNAME(TP)+" grins evilly as "+HE_SHE(TP)+" starts fiddling "+
      "around with the "+trigger[0]->short()+".\nYou wonder what "+
      HE_SHE(TP)+" is doing to it?\n");
    time = (90 - TP->query_skill(SS_SET_TRAPS)) / 2;
    para = paralyze(time);
    trap_id = set_alarm(itof(time-1),0.0,&set_up_snare(rope,trigger[0],TP));
    para->move(TP,1);
    return 1;
}

void
set_up_snare(object rope, object trigger, object player) 
{
    int quality = TASK_SIMPLE;
    int skill, myint, guildstat;
    object shadow;

    if (!present(trigger, ENV(TP)))
    {
	write("But the "+trigger->short()+" isn't here anymore!\n");
	return;
    }
    silent = 1;
    //   Determine the quality of this trap based on a few things.
    //     If it's inside -300 to the quality
    if (ENV(player)->query_prop(ROOM_I_INSIDE))
	quality =- 300;
    //     How good is the trapper at setting it?
    skill = player->query_skill(SS_SET_TRAPS);
    guildstat = player->query_stat(SS_LAYMAN);
    myint = player->query_stat(SS_INT);

    quality +=  (skill*2) + (guildstat * 3) / 2 + myint;
    CHECK_MINIMUM(quality);
    CHECK_MAXIMUM(quality);

    setuid(); seteuid(getuid());
    shadow = clone_object(SNARE_TRAP);
    shadow->shadow_me(trigger);
    trigger->set_trap_setter(player->query_real_name());
    trigger->set_trap_qual(quality);
    trigger->set_up_trap();
    if (rope)
    {
	trigger->set_where_rope_from(MASTER_OB(rope));
	rope->remove_object();
    }
    write("You finish setting your snare trap and peer mischievously "+
      "around the area looking for a victim.\n");
    say(QCTNAME(TP)+" finishes tinkering with the "+trigger->short()+
      " and starts to peer mischievously around, apparently looking "+
      "for something.\n");
}

int
pittrap(string str)
{
    object shovel, para;
    int time, size;

    if (!str)
    {
	notify_fail("How big of a hole do you want to make "+
	  "it?\nHuge, large, medium or small?\n");
	return 0;
    }

    switch (lower_case(str))
    {
    case "huge":
	size = 50;
	break;
    case "large":
	size = 35;
	break;
    case "medium":
	size = 20;
	break;
    case "small":
	size = 10;
	break;
    default:
	notify_fail("Huge, large, medium or small are the only valid choices "+
	  "for the pit trap.\n");
	return 0;
    }
    if (ENV(TP)->query_is_pit_room())
    {
	notify_fail("You can't dig a hole a hole!!\n");
	return 0;
    }
    if (ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
	notify_fail("You can't place this trap in a room which is indoors!\n");
	return 0;
    }
    if (present("trickster_pit_trap",ENV(TP)) || present("trickster_disarmed_pit_trap",ENV(TP)))
    {
	notify_fail("But there is already a pit trap here!!\n");
	return 0;
    }
    shovel = present("shovel",TP);
    //  WIzards don't need no stinking shovel
    if (!shovel && !TP->query_wiz_level())
    {
	notify_fail("You need a shovel to dig your trap silly!\n");
	return 0;
    }

    time = (100 - TP->query_skill(SS_SET_TRAPS) + size) / 2;
    para = paralyze(time);
    trap_id = set_alarm(itof(time - 1),0.0,&set_pit_trap(shovel,TP,size));
    para->move(TP,1);
    write("You start dig madly away at the ground in order to make a "+
      str+" hole in the ground for your pit trap.\n");
    say(QCTNAME(TP)+" digs madly away at the ground with "+HIS_HER(TP)+
      " shovel, digging a hole for some strange purpose.\n");
    return 1;
}

void
set_pit_trap(object shovel, object player, int size) 
{
    object trap;
    int skill, mywis, guildstat, quality = TASK_SIMPLE;

    silent = 1;
    skill = player->query_skill(SS_SET_TRAPS);
    mywis = player->query_stat(SS_WIS); //Must be wise to know where to place it
    guildstat = player->query_stat(SS_LAYMAN);
    quality += (skill * 3) + mywis + guildstat;
    CHECK_MINIMUM(quality);
    CHECK_MAXIMUM(quality);

    setuid(); seteuid(getuid());
    trap = clone_object(PIT_TRAP);
    trap->set_trapsetter(player->query_real_name());
    trap->set_trapsize(size);
    trap->set_trapqual(quality);
    trap->move(ENV(player));
    write("You cover your hole up with some leaves and smile happily as "+
      "your wonderful pit trap is finally finished.\n");
    say(QCTNAME(player)+" covers up a hole with some leaves and starts smiling "+
      "happily, as if "+HE_SHE(player)+" has created some mischievous "+
      "masterpiece.\n");
    // 50% chance of the shovel getting broken.
    if (shovel && !random(2))
    {
	write("Upon finishing your trap your shovel falls apart is becomes "+
	  "useless!\n");
	say(QCTNAME(player)+"'s shovel falls apart and becomes useless after "+
	  "completing "+HIS_HER(player)+" trap!\n");
	shovel->remove_object();
    }
}

int
oilslick(string str)
{
    object para, flask;
    int time;

    if (str)
    {
	notify_fail("Oilslick what?\n");
	return 0;
    }
    flask = present("lamp oil",TP);
    if (present("trickster_oil_slick",ENV(TP)))
    {
	notify_fail("But there is already an oil slick here!\n");
	return 0;
    }
    //   Wizards don't need no silly lamp oil to do this
    if (!flask && !TP->query_wiz_level())
    {
	notify_fail("You need an oil flask to set this trap up.\n");
	return 0;
    }
    time = (100 - TP->query_skill(SS_SET_TRAPS))/5;
    para = paralyze(time);
    para->move(TP,1);
    trap_id = set_alarm(itof(time - 1),0.0,&set_up_slick(flask,TP));
    write("You slowly start pouring an oil flask on the ground "+
      "in order to make the surrounding area all slippery!\n");
    say(QCTNAME(TP)+" starts pouring the "+flask->short()+
      " all over the ground for some strange reason.\n");
    return 1;
}


void
set_up_slick(object flask, object player)
{
    object trap;
    int skill, mydex, guildstat, quality = 100;

    silent = 1;
    skill = player->query_skill(SS_SET_TRAPS);
    mydex = player->query_skill(SS_DEX); // Must have some dex to do this right
    guildstat = player->query_stat(SS_LAYMAN);
    quality += (skill * 2) + guildstat + mydex;
    CHECK_MINIMUM(quality);
    CHECK_MAXIMUM(quality);

    setuid(); seteuid(getuid());
    trap = clone_object(SLICK_TRAP);
    trap->set_trap_setter(player->query_real_name());
    trap->set_trap_qual(quality);
    trap->move(ENV(player));
    flask->remove_object();
    write("You toss the flask away having completed your task of "+
      "making the entire area extremely slippery.\n");
    say("Having completed pouring the flask all over the ground "+
      QTNAME(player)+" tosses it aside!\n");
    player->command("tgrin");
    return;
}

int
tripwire(string str)
{
    int time;
    object para, wire;

    if (member_array(str,ENV(TP)->query_exit_cmds()) < 0)
    {
	notify_fail("You are not able to set up a trip wire in that "+
	  "direction.\n");
	return 0;
    }
    if (present("trickster_trip_object",ENV(TP)))
    {
	notify_fail("But there is already a trip wire already in the room "+
	  "here!\n");
	return 0;
    }
    wire = present("wire",TP);
    if (!wire)
	wire = present("rope",TP);
    //   Wizards don't need no silly wires
    if (!wire && !TP->query_wiz_level())
    {
	notify_fail("But you have no wire to make a trip wire with!\n");
	return 0;
    }
    time = (80 - TP->query_skill(SS_SET_TRAPS)) / 2;
    trap_id = set_alarm(itof(time - 1),0.0,&set_up_tripwire(wire,TP,str));
    para = paralyze(time);
    para->move(TP,1);
    write("You start setting up your trip wire in order to cause "+
      "people to trip when they walk "+str+".\n");
    say(QCTNAME(TP)+" starts to do something around the "+str+
      " exit.\n");
    return 1;
}

void
set_up_tripwire(object wire, object player, string direction)
{
    string filename;
    object trap;
    int qual = 0;

    silent = 1;
    setuid(); seteuid(getuid());
    trap = clone_object(TRIP_TRAP);
    trap->move(ENV(player));
    if (wire)
    {
	filename = MASTER_OB(wire);
    }
    trap->set_up_trap(qual,player->query_real_name(),direction,filename);
    write("You finish setting your trip wire and smile wickedly unable "+
      "to control your excitement at the thought of someone falling and "+
      "tripping on your trap!\n");
    say(QCTNAME(TP)+" finishes stringing up a trip wire in the room as "+
      HE_SHE(TP)+" smiles wickedly at some strange thought.\n");
    return;
}

int
attach(string str)
{
    object trap;

    if (str != "laughgas")
    {
	notify_fail("Attach what?\n");
	return 0;
    }
    if (TP->query_charge(4) <= 0)
    {
	notify_fail("But you have no laughing gas to attach to the trap!\n");
	return 0;
    }
    trap = present("trickster_trip_object",ENV(TP));
    if (!trap)
    {
	notify_fail("But there is no trip wire here to attach some "+
	  "laughing gas to!\n");
	return 0;
    }
    if (trap->query_armed())
    {
	notify_fail("But the trip wire already has a vial of laugh gas on it!!\n");
	return 0;
    }
    write("You grin evilly as you add a vial of laughgas to the cleverly "+
      "hidden trip wire.\n");
    say(QCTNAME(TP)+" grins evilly as "+HE_SHE(TP)+" starts tinkering with "+
      "a trap in the room!\n");
    trap->arm_trap();
    //   Remove laughing gas from player
    TP->remove_charge(4);
    return 1;
}

int
bucket(string str)
{
    object bucket, door;

    if (!str)
    {
	notify_fail("Place a bucket on what?\n");
	return 0;
    }
    // Find the door
    if (!objectp(door = FIND_STR_IN_OBJECT(str,ENV(TP))[0]))
    {
	notify_fail("Place a bucket on what?\n");
	return 0;
    }
    if (!function_exists("create_door",door))
    {
	notify_fail("You can not place your bucket on the "+str+
	  " since it is not a door.\n");
	return 0;
    }
    // Check if door is open
    if (door->query_open())
    {
	notify_fail("Make sure the "+str+" is closed, attempting to place "+
	  "a bucket on an open door defeats the purpose of placing it there.\n");
	return 0;
    }
    // Find the bucket
    if (!objectp(bucket = present("bucket",TP)))
    {
	notify_fail("But you have no bucket to place on the "+str+".\n");
	return 0;
    }
    if (!bucket->query_prop(TRICKSTER_BUCKET_PROP))
    {
	notify_fail("The bucket doesn't seem to have been prepared properly.\n");
	return 0;
    }
    return 1;
}
