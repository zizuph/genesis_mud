/*
 *    Igneous' Pet :)
 *    
 *    Copyright (C) Chad Richardson, Apr 10, 1997
 *
 *    A pet puppy which is to be sold buy a hobbit npc in the Shire
 *    A prototype of a "tag-a-long" npc 
 *    Possible extensitions familiars and pack-animals.
 */

#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD  0
#define H_BACK  1
#define H_LPAW  2
#define H_RPAW  3
#define H_LHPAW 4
#define H_RHPAW 5

#define DOG_LEAVES_FOR_GOOD    120 + random(61)
#define DOG_WAITS_FOR_LINKDEAD 30 * 60
#define FOLLOW_SHADOW          "/d/Khalakhor/igneous/follow.c"
#define SOULDESC(x)            (TO->add_prop(LIVE_S_SOULEXTRA, x))

// Debug Defines :)
#define DEBUGGING

#ifdef  DEBUGGING
#define DEBUG_WHO find_player("igneous")
#define DEBUG(s)  DEBUG_WHO->catch_msg("DOG: " + s + "\n")
#else
#define DEBUG(s)
#endif
// End of Debuging defines :)


inherit "/std/creature";
inherit "/std/combat/unarmed";

//  Prototypes
void   react_to_masters_death();
void   cower_behind_master();
void   eat_dog_food(object food);
void   found_new_master(object master);
void   stop_fighting(object enemy);
void   master_returned();
int    masters_commands(string str);
mixed  my_no_give();
void   take_off();


//  Gobal Variables
int Cower_alarm = 0, Dead_alarm = 0, Eat_alarm = 0,
Leave_alarm = 0, Searching = 0;

object gMaster;


/*
 * Function name :  Create_creature
 * Description   :  Create the creature or in our case our puppy
 */
void
create_creature()
{
    if (!IS_CLONE) 
	return;
    set_name("rover");
    add_name(({"dog","doggie","mutt"}));
    set_long("@@my_long@@");
    set_adj(({"floppy-eared","drooling"}));
    set_race_name("puppy");
    set_alignment(150 + random(201));
    set_gender(G_MALE);

    set_stats(({15,25,35,10,10,30}));

    set_skill(SS_UNARM_COMBAT, 30 + random(10));
    set_skill(SS_DEFENCE,35 + random(10));
    set_skill(SS_AWARENESS, 60 + random(21));
    set_skill(SS_HIDE, 40 + random(11));
    set_skill(SS_SNEAK, 35 + random(11));
    set_skill(SS_LOC_SENSE, 65 + random(21));
    set_skill(SS_CLIMB, 15 + random(21));
    set_skill(SS_SWIM, 50 + random(21));
    set_skill(SS_HUNTING, 45 + random(11));

    set_attack_unarmed(A_BITE, 8, 17, W_IMPALE, 50, "bite");
    set_attack_unarmed(A_LPAW, 16, 5, W_SLASH,  25, "left paw");
    set_attack_unarmed(A_RPAW, 16, 5, W_SLASH,  25, "right paw");

    set_hitloc_unarmed(H_HEAD,  ({7,5,6}),    20, "head");
    set_hitloc_unarmed(H_BACK,  ({16,15,16}), 40, "furry back");
    set_hitloc_unarmed(H_RPAW,  ({10,6,14}),  15, "right paw");
    set_hitloc_unarmed(H_LPAW,  ({10,6,14}),  15, "left paw");
    set_hitloc_unarmed(H_RHPAW, ({10,6,14}),   5, "right hind leg");
    set_hitloc_unarmed(H_LHPAW, ({10,6,14}),   5, "left hind leg");

    seteuid(getuid(TO));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, my_no_give);

}

/*
 * Function name :  My_long
 * Description   :  Determines the long description of the puppy
 * Returns       :  the long description.
 */
string
my_long()
{
    string str;

    if (TP == gMaster)
	str = query_name();
    else
	str = "The "+ query_nonmet_name();

    if (present(gMaster,ENV(TO)))
	if (TP == gMaster)
	    str += " is your pet.  ";
	else
	    str += " is "+gMaster->query_the_name(TP)+"'s pet.  ";
    else
	str += " is somebodies pet.  ";

    str += TO->query_The_name(TP)+" is constanly barking and jumping around "+
    "playing at your feet.  "+CAP(HE_SHE(TO))+" is about the most cuddly "+
    "puppy you've ever seen.\n";

    if (Searching)
	str += CAP(HE_SHE(TO))+" seems to be searching for someone at "+
	"the moment.\n";
    if (Leave_alarm)
	str += CAP(HE_SHE(TO))+" seems to be lonely, and has a hungry "+
	"look in "+HIS_HER(TO)+" eyes.\n";

    if (query_fatigue() <= 5)
	str += CAP(HE_SHE(TO)) + " is panting heavily from fatigue.\n";

    str += CAP(HE_SHE(TO)) + " is wearing a little leather collar with the "+
    "name '"+query_name()+"' printed on it.\n";

    return str;
}

/*
 * Function name : My_no_give
 * Description   : Determines if the puppy accpets gives from players
 * Returns       : Mixed value
 */
mixed
my_no_give()
{
    if (TP == gMaster || !gMaster)
	return 0;

    return " won't accept gifts from you.\n";
}

/*
 * Function name : Query_m_in (MASKED)
 * Returns       : The puppy's in description
 */
public string
query_m_in()
{
    if (query_prop(LIVE_I_SNEAK))
	return "arrives.";
    if (gMaster)
	if (!random(10))
	    return "arrives, nearly tripping over one of "+HIS_HER(TO)+
	    " floppy ears.";
	else
	    return "arrives wagging "+HIS_HER(TO)+" tail.";
    else
	return "arrives looking for "+HIS_HER(TO)+" master.";
}

/*
 * Function name : Query_m_out (MASKED)
 * Returns       : They puppy's out description
 */
public string
query_m_out()
{
    if (query_prop(LIVE_I_SNEAK))
	return "leaves";
    if (gMaster)
	return "quickly runs after "+HIS_HER(TO)+" master, towards the";
    else
	return "leaves";
}

/*
 * Function name : Init_living (MASKED)
 * Description   : initialize ceratin command and functions when livings
 *                 come in contact with this npc
 */
void
init_living()
{
    ::init_living();
    if (Searching && TP == gMaster)
	set_alarm(1.0,0.0, &master_returned());
    if (TP == gMaster)
	add_action(masters_commands,"command");
}

//   Possible extentions (sit, fetch, attack)

/*
 * Function name : Masters_commands
 * Arguments     : str - What command I want to do
 * Description   : Commands which the master of this puppy can make
 *                 the puppy do.
 * Returns       : 1/0
 */
int
masters_commands(string str)
{
    NF(CAP(query_verb()) +" your pet to do what?\n");   

    if (!str) return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
	NF("You don't see your pet around here at the moment.\n");
	return 0;
    }
    switch (str)
    {
    case "stay":
	TP->catch_msg("You command "+QTNAME(TO)+" to stay.\n");
	say(QCTNAME(TP) + " commands "+QTNAME(TO)+" to stay.\n");
	TP->stop_following_master();
	Searching = 1;
	break;
    case "follow":
	TP->catch_msg("You command "+QTNAME(TO)+" to follow you again.\n");
	say(QCTNAME(TP) + " commands "+QTNAME(TO)+" to follow "+
	  HIM_HER(TP)+".\n");
	TP->start_following_master();
	Searching = 0;
	break;
    case "roll over":
	TP->catch_msg("You command "+QTNAME(TO)+" roll over.\n");
	command("emote rolls over onto "+HIS_HER(TO)+" belly in a "+
	  "playful fashion.");
	break;
    case "beg":
	TP->catch_msg("You command "+QTNAME(TO)+" to beg.\n");
	TP->catch_msg(QCTNAME(TO)+" looks up at you with "+HIS_HER(TO)+
	  " pleading, puppy dog eyes in a begging fashion.\n");
	say(QCTNAME(TO)+" looks up at "+QTNAME(TP)+" with "+HIS_HER(TO)+
	  " pleading, puppy dog eyes in a begging fashion.\n");
	SOULDESC("is begging");
	break;
    case "play dead":
	TP->catch_msg("You command "+QTNAME(TO)+" to play dead.\n");
	command("emote rolls over onto "+HIS_HER(TO)+" back and becomes "+
	  "deathly still.");
	set_alarm(3.0,0.0,&command("emote jumps to "+HIS_HER(TO)+" feet "+
	    "and wags "+HIS_HER(TO)+" tail happily."));
	break;
    case "speak":
	TP->catch_msg("You command "+QTNAME(TO)+" to speak.\n");
	command("emote barks loudly.");
	SOULDESC("barking loudly");
	break;
    case "go home":
	TP->catch_msg("You command "+QTNAME(TO)+" to go home.\n");
	command("emote with a sad look on "+HIS_HER(TO)+" face, "+
	  HE_SHE(TO)+" makes "+HIS_HER(TO)+" way home.");
	set_alarm(1.0,0.0,&remove_object());
	break;
    default:
	return 0;
    }
    return 1;
}

/*
 * Function name : Enter_inv (MASKED)
 * Arguments     : ob - object which entered the inv
 *                 from - where the ob came from
 * Description   : Tests to see if the ob is food from the puppy's master
 *                 otherwise the dog drops the object
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);

    if (function_exists("create_food",ob) && !Eat_alarm)
    {
	Eat_alarm = set_alarm(2.0,0.0, &eat_dog_food(ob));
	if (Leave_alarm && living(from))
	{
	    set_alarm(3.0,0.0, &found_new_master(from));
	    Leave_alarm = 0;
	}		   
    }  
    else if (!function_exists("create_food",ob))
	set_alarm(itof(random(4)+1),0.0, &command("drop "+ob->query_name()));
}

/*
 * Function name : Remove_object (MASKED)
 * Description   : Here to make sure the shadow that the puppy uses to follow
 *                 It's master is removed.
 * Returns       : 1/0
 */
public int
remove_object()
{
    if (gMaster)
	gMaster->remove_master_follow_shadow();

    return ::remove_object();
}

/*
 * Function name : Attacked_by (MASKED)
 * Arguments     : attacker - the object that attacked me
 * Description   : Here to enable the dog to move behind it's master
 *                 out of harms way.
 */
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    if (!Cower_alarm && gMaster && attacker != gMaster)
	Cower_alarm = set_alarm(itof(random(6)+5),0.0,&cower_behind_master());
}


/*
 * Function name : Cower_behind_master
 * Description   : Finds all the puppy's enemies and forces the to stop
 *                 fighting it by taking cover underneeth it's Master's
 *                 legs.
 */
void
cower_behind_master()
{
    object *enemies;

    Cower_alarm = 0;    

    if (!gMaster)
	return;
    if (!present(gMaster, ENV(TO)))
	return;

    enemies = filter(query_enemy(-1), &operator (==) (,TO) @
      &->query_attack());
    map(enemies, &stop_fighting());

    enemies->catch_msg(QCTNAME(TO) + " wimpers and hides between "+
      QTNAME(gMaster) + "'s legs, making it impossible to continue "+
      "your attack.\n");
    gMaster->catch_msg(QCTNAME(TO) + " wimpers and hides between "+
      "your legs, preventing "+HIS_HER(TO)+" enemies from "+
      "attacking "+HIM_HER(TO)+".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " wimpers and hides between "+ 
      QTNAME(gMaster) + "'s legs, preventing "+HIS_HER(TO)+" enemies from "+
      "attacking "+HIM_HER(TO)+".\n", enemies + ({gMaster}));       
}

/*
 * Function name : Stop_fighting
 * Arguments     : enemy - the enemy we want to make peace with
 * Description   : creates a peace between the puppy and it's enemy
 */
void
stop_fighting(object enemy)
{
    enemy->stop_fight(TO);
    TO->stop_fight(enemy);
    if (member_array(enemy,gMaster->query_enemy(-1)) != -1 && 
      present(gMaster, ENV(enemy)))
	enemy->attack_object(gMaster);
}

/*
 * Function name : Set_master
 * Arguments     : name - the name (or object pointer) of the master
 * Description   : Sets the master of this puppy
 */
void
set_master(mixed name)
{
    object master;

    // But we already got a Master, you see
    if (gMaster)
	return;

    //  The Masters name was given
    if (stringp(name))
	master = find_player(lower_case(name));

    //  A pointer to the Master was given
    if (objectp(name))
	master = name;

    if (!master)
	return;

    if (Leave_alarm)
    {
	remove_alarm(Leave_alarm);
	Leave_alarm = 0;
    }
    setuid(); seteuid(getuid());
    clone_object(FOLLOW_SHADOW)->follow_master(master, TO);
    gMaster = master;
}

/*
 * Function name : Remove_master
 * Description   : Removes the master of this puppy
 */
void
remove_master()
{   
    //  Got no Master already
    if (!gMaster)
	return;

    gMaster->remove_master_follow_shadow();
    gMaster = 0;
}

/*
 * Function name : Query_master
 * Description   : A query to find out who the master is
 * Returns       : Who the master is.
 */
string
query_master()
{
    if (!gMaster)
	return TO->query_name() + " has no Master.";

    return TO->query_name() + "'s Master currently is "+
    gMaster->query_name() + ".";
}

/*
 * Function name : Found_new_master
 * Arguments     : master - the new master
 * Description   : If the dog lost his old master he'll try and find a new one.
 */
void
found_new_master(object master)
{
    //  Already got a Master
    if (gMaster)
	return;

    //  We found some other sap to hang around with :)
    if (Leave_alarm)
    {
	remove_alarm(Leave_alarm);
	Leave_alarm = 0;
    }
    set_master(master);
    if (present(master,ENV(TO)))
	master->catch_msg(QCTNAME(TO) + " jumps excitied all around, as "+
	  HE_SHE(TO) + " has picked you as "+HIS_HER(TO)+" new master.\n");
    tell_room(ENV(TO),QCTNAME(TO)+" jumps excitied all around, as "+
      HE_SHE(TO) + " has found "+HIM_HER(TO)+"self a new master.\n",
      ({TO,master}));
}


//  all notify_master_* functions are called from the follow shadow.

/*
 * Function name : Notify_mastered_died
 * Description   : Called from the follow shadow, lets the puppy know
 *                 when it's master died.
 */
void
notify_master_died()
{
    if (!Dead_alarm)
	Dead_alarm = set_alarm(1.0,0.0,&react_to_masters_death());
}

/*
 * Function name : Notify_master_removed
 * Description   : Called from the follow shadow, lets the puppy know
 *                 if it's master quit or was destructed by some bad,
 *                 mishievous wizard ;)
 */
void
notify_master_removed()
{
    if (Dead_alarm || !objectp(gMaster))
	return;
    gMaster = 0;

    set_alarm(1.0,0.0,&command("emote looks all sad and loney."));
    if (!Leave_alarm)
	Leave_alarm = set_alarm(itof(DOG_LEAVES_FOR_GOOD),0.0,&take_off());
}

/*
 * Function name : Notify_master_linkdead
 * Description   : Called from the follow shadow, notifies the puppy when
 *                 it's master goes link_dead
 */
void
notify_master_linkdead()
{
    if (!gMaster)
	return;
    if (!Leave_alarm)
	Leave_alarm = set_alarm(itof(DOG_WAITS_FOR_LINKDEAD),0.0,&take_off());

    Searching = 1;
    set_alarm(1.0,0.0,&command("emote searches frantically for "+HIS_HER(TO)+
	" master."));
}

/*
 * Function name : Eat_dog_food
 * Arguments     : food - the food the puppy was given to eat
 * Description   : The dog eats food, and expects to be fed regularly
 *                  Or it will leave, this is here to make sure he eats it.
 */
void
eat_dog_food(object food)
{
    Eat_alarm = 0;
    command("emote sniffs at "+LANG_THESHORT(food));
    command("eat all");
}

/*
 * Function name : Master_returned
 * Description   : If the master and dog get separated and the do go 
 *                 searching for the master this function is called when
 *                 the two come in contact.
 */
void
master_returned()
{
    if (!present(gMaster, ENV(TO)) || !Searching)
	return;
    if (Leave_alarm)
    {
	remove_alarm(Leave_alarm);
	Leave_alarm = 0;
    }
    gMaster->catch_msg(QCTNAME(TO) + " pants happily at your arrival.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " pants happily at "+HIS_HER(TO)+
      " masters arrival.\n", ({TO,gMaster}));
    SOULDESC("panting happily");
    command("lick "+ gMaster->query_real_name());
    Searching = 0;
}

/*
 * Function name : React_to_masters_death
 * Description   : Make the dog reacted to the death of it's master.
 */
void 
react_to_masters_death()
{  
    if (!Dead_alarm)
	return;

    Dead_alarm = 0;

    if (!Leave_alarm)
	Leave_alarm = set_alarm(itof(DOG_LEAVES_FOR_GOOD),0.0,&take_off());
    command("emote howls in morning at "+HIS_HER(TO)+" masters death.");
    if (present("corpse",ENV(TO))->query_met_name() == gMaster->query_name())
	set_alarm(2.5,0.0,&command("emote stares at his master's corpse "+
	    "letting out a tiny whimper of sarrow."));
}

/*
 * Function name : Take_off
 * Description   : Tired of this crowd the puppy will take off for good.
 */
void
take_off()
{
    if (gMaster)
	return;
    tell_room(ENV(TO),"Unable to find "+HIM_HER(TO)+"self a new master "+
      QTNAME(TO)+" wanders off in search of home.\n",({TO}));
    remove_object();
}


//  Here are all the npc's acts and reactions to emotes.

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    switch (emote)
    {
    case "kick": case "knee": case "grope":
	set_alarm(0.2,0.0,&command("emote yelps in pain!"));
	set_alarm(0.5,0.0,&command("sniff"));
	break;
    case "pat":
	set_alarm(0.5,0.0,&command("emote starts to wag "+HIS_HER(TO)+
	    " tail vigorously to and fro."));
	break;
    case "ruffle":
	set_alarm(0.5,0.0,&command("drool"));
	set_alarm(1.0,0.0,&command("emote wags "+HIS_HER(TO)+
	    " tail rapidly."));
	set_alarm(1.5,0.0,&command("bounce all"));
	break;
    case "hug":
	set_alarm(0.5,0.0,&command("emote wags "+HIS_HER(TO)+" tail happily."));
	break;
    case "lick":
	set_alarm(0.5,0.0,&command("lick "+actor->query_real_name()+
	    " excessively"));
	break;
    } 
}

public void
emote_hook_onlooker(string emote,object actor,string adverb,object *oblist)
{

    //  Only react if the emote was preformed on our Master
    if (member_array(gMaster,oblist) == -1)
	return;

    switch (emote)
    {
    case "kick":  case "knee":
	set_alarm(1.0,0.0,&command("growl dangerously at "+
	    actor->query_real_name()));
	break;
    case "tackle":
	set_alarm(0.5,0.0,&command("tackle "+actor->query_real_name()));
	set_alarm(1.0,0.0,&command("growl menacingly at "+
	    actor->query_real_name()));
	break;
    }
}
