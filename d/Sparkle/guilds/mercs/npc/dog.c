/*
 * Mercenary Lord Hunting Dogs (/d/Genesis/guilds/merc/npc/dog)
 *     by Morrigan Sept 2002
 *
 * Updated for Sparkle domain /d/Sparkle 2006-01-10 by Lunatari
 * 
 */
#include "../merc.h"

inherit GEN_STEED_FEED

inherit "/std/creature";
inherit "/std/combat/unarmed.c";
inherit "/lib/commands";
inherit "/std/act/action";
inherit "/std/act/chat";

#define DELAY			20.0
#define LIVE_I_DOG_ATTACKER	"_live_i_dog_attacker_"
#define MESSAGE			(MOBJ + "scroll")
#define TEMP_ROOM		(MROOM + "dogs_temp")
#define ATTACKER_FORGIVE_TIME   3600
#define HIDER_FORGIVE_TIME      600
#define LORD_SAID_HUSH		"_merc_lord_said_hush"
#define LED_BY_OWNER   (query_leader()->query_name() == query_owner() ? 1 : 0)
#define LEAD_SHADOW 		(MOBJ + "leader_shadow")

// --- globals ---
static string  Owner, Barding;
static string gComm1, gComm2, gMessage, gSender, gWho;
static object Leader;
int gAlarmId   = 0;
mapping agg = ([ ]);

// --- prototypes ---

void add_acts();
public int custom_can_see(object me, object them);
public void attack_func(object ob);
public void fly_to_owner();
public void fly_away();
public string query_message() { return gMessage; }
public string query_sender() { return gSender; }
public string query_recipient() { return gWho; }
public void   set_owner(object who) { Owner = who->query_name(); }
public string query_owner()         { return Owner; }
public int query_merc_dog()         { return 1; }
public void   set_barding(string s) { Barding = s; }
public object query_leader()        { return Leader; }
public varargs string short_old(object for_obj);

public varargs string
short_old(object for_obj)
{
   return ::short(for_obj);
}

public string query_barding()       
{ 
    if (!strlen(Barding))
        return "black dragon on a red background";

    return Barding;
}

string
long_desc()
{
    string str = ", wearing a harness with a crest of a "+
        query_barding()+" that covers "+POSSESSIVE(TO)+" chest";

    return "A " + short_old() + str + ". The dogs can be ordered "+
	"to do things with 'dorder', if you are leading them.\n";
}

void
create_creature()
{
    set_name("dog");
    set_adj(({"hunting", "messenger"}));
    set_gender(0);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 200);
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);

    set_stats(({ 75, 75, 90, 30, 30, 120 }));
    set_skill(SS_CLIMB, 75);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_SWIM, 50);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRACKING, 90);
    set_long(long_desc);

    set_m_in("paces in");
    set_m_out("paces");

    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));

    set_allowed_food(({ "meat", "steak", "chicken", "ham", "beef",
	"venison", "rabbit", "deer", "pig", "corpse" }));

   set_attack_unarmed(0, 10, 10, W_IMPALE | W_SLASH, 80, "teeth");
   set_attack_unarmed(1, 15, 20, W_BLUDGEON, 10, "right fore paw");
   set_attack_unarmed(2, 15, 20, W_BLUDGEON, 10, "left fore paw");

   set_hitloc_unarmed(0, 10, 15, "head");
   set_hitloc_unarmed(1, 10, 40, "body");
   set_hitloc_unarmed(2, 15, 20, "foreleg");
   set_hitloc_unarmed(3, 10, 20, "hindleg");
   set_hitloc_unarmed(4, 10, 5, "tail");

   set_alarm(1.0, 0.0, &add_acts());
}

void
add_acts()
{
    string pos = POSSESSIVE(TO);
    string pro = PRONOUN(TO);

    set_act_time(40);
    add_act("emote scratches "+pos+ " side with a hind leg.");
    add_act("emote sits down and looks around.");
    add_act("emote sniffs around on the ground.");
    add_act("emote looks to the side, as if "+pro+" heard something.");
    add_act("emote prances around excitedly for a moment.");
    add_act("emote licks "+pos+" right paw briefly.");
    add_act("emote licks "+pos+" left paw briefly.");
    add_act("emote licks "+pos+" right hind leg.");
    add_act("emote licks "+pos+" left hind leg.");
    add_act("emote scratches "+pos+" neck with a hind leg.");
    add_act("emote paces around the area restlessly.");
    add_act("emote chews on something "+pro+" found.");
    add_act("emote whimpers as "+pro+" hears something in the distance.");
    add_act("emote chews on "+pos+" tail.");
    add_act("emote lays down on the ground.");
    add_act("emote wags "+pos+" tail.");

    set_cact_time(20);
    add_cact("emote growls viciously and bares "+POSSESSIVE(TO)+" sharp "+
	"teeth!");
}


/* LEAD AND LEAVE FUNCTIONS */

public void
lead_hook(object o)
{
   if (calling_function(-1) != "lead_dog")
	return;

   o->catch_tell("You motion for the " + short() + " to follow.\n");
   tell_room(environment(), QCTNAME(o) + " motions for the "+short() + 
       " to follow.\n", o);
}

public void
unlead_hook(object o)
{
   if (calling_function(-1) != "leave_dog")
	return;

   o->catch_tell("You motion for the " + short() + " to stay.\n");
   tell_room(environment(), QCTNAME(o) + " motions for the "+
	short()+" to stay.\n", o);
}

public int
can_lead(object o)
{
    if (member_array(o->query_name(), query_prop(LIVE_I_DOG_ATTACKER)) != -1)
    {
        o->catch_tell("The "+short()+" seems to remember you.\n");
        command("growl vic "+o->query_name());
	return 0;
    }

    if (member_array(o->query_name(), 
	MCREST->query_followers(query_owner())) == -1 &&
	o->query_name() != query_owner() &&
	o->query_name() != C(gWho) &&
	environment(this_object()) != find_object(MKENNEL))
    {
        if (query_verb() == "dorder")
            o->catch_tell("The "+short()+" doesn't seem to recognize you.\n");

        return 0;
    }

    if (query_verb() == "dorder" && o->query_name() != query_owner())
    o->catch_tell("The "+short()+" recognizes you as a friend.\n");
    return 1;
}

/* Function name: do_lead
 * Description:   Let a living lead this steed.
 * Arguments:     object: the leader to be
 * Returns:       int success
 */
public int
do_lead(object o)
{
   object shadow;

   if (!can_lead(o))
      return 1;

   Leader = o;
   // See if the living is already leading another horse
   if (!Leader->query_leading_mercdog())
   {
      shadow = clone_object(LEAD_SHADOW);
      shadow->shadow_me(Leader);
   }

   Leader->add_mercdog_follow(this_object());

   // Give message that living starts leading the steed
   lead_hook(Leader);
   return 1;
}

/* Function name: do_unlead
 * Description:   Let the leader of this steed not lead it anymore.
 * Arguments:     object the supposed to be leader, if not the right
 *                       leader is passed, the function fails.
 *                int - optional: notify the leader's shadow that the leader
 *                   is no longer leading the steed.
 * Returns:       int success
 */
public varargs int
do_unlead(object o, int notify_shadow = 0)
{
   if (Leader != o)
      return 0;
   if (notify_shadow)
      Leader->remove_mercdog_follow(this_object());
      
   // Give message that living stops leading the steed.
   unlead_hook(Leader);
   Leader = 0;
   return 1;
}

/* Function name: lead
 * Description:   lead this steed somewhere
 * Arguments:     string - the steed to lead
 * Returns:       int 1 if successful
 */
public int
lead_dog(string s)
{
   object *o_list;
   object steed;

   if (!s || !sizeof(o_list = 
      FIND_STR_IN_ARR(s, all_inventory(environment(this_player())))))
      return 0;
   if (sizeof(o_list) > 1)
      return 0;
   steed = o_list[0];

   // check if it's a merc dog
   if (!steed->query_merc_dog())
      return 0;

   if (objectp(steed->query_leader()) &&
	TP->query_name() == query_owner() &&
	steed->query_leader() != TP)
   {
	do_unlead(steed->query_leader(), 1);
	return steed->do_lead(TP);
   }

   // check if we have a leader already
   if (objectp(steed->query_leader()))
   {
      NF("The " + steed->short() + " is already lead by someone.\n");
      return 0;
   }

   return steed->do_lead(this_player());
}

/* Function name: unlead
 * Description:   Leave the steed.
 * Arguments:     string: the object description the living wants to leave.
 * Returns:       int success
 */
public int
leave_dog(string s)
{
   object *o_list;
   object steed;

   if (!strlen(s) && query_leader() == this_player())
   {
       steed = this_object();
   }
   else if (!s || !sizeof(o_list = 
      FIND_STR_IN_ARR(s, all_inventory(environment(this_player())))))
      return 0;

   if (sizeof(o_list))
      if (sizeof(o_list) > 1)   
          return 0;
         else
          steed = o_list[0];

   // check if it's a steed
   if (!steed->query_merc_dog())
      return 0;

   return steed->do_unlead(this_player(), 1);
}

/* VARIOUS ACTIONS */

int
water_horse(string str)
{
    object here = E(TO);

    NF("There is no water here for your "+short_old()+" to drink.\n");
    if (!(here->query_prop(ROOM_I_TYPE) == 1) && 
      (!here->query_prop(OBJ_I_CONTAIN_WATER)))
	return 0;

    NF("Your "+short_old()+" doesn't seem to be thirsty.\n");
    if (query_soaked() + 100 >= query_prop(LIVE_I_MAX_DRINK))
	return 0;

    tell_room(E(TO), "The "+short_old()+" drinks from the water.\n");
    set_soaked(query_soaked() + 100);
    return 1;
}

int
feed_horse(string str)
{
    object here = E(TO), corpse;

    NF("There is nothing here for your "+short_old()+" to feed on.\n");
    if (!(corpse = present("corpse", here)))
	return 0;

    NF("Your "+short_old()+" doesn't seem to be hungry.\n");
    if (query_stuffed() + 25 >= query_prop(LIVE_I_MAX_EAT))
    {
	write("Your "+short_old()+" doesn't seem to be hungry.\n");
	return 1;
    }

    tell_room(E(TO), "The "+short_old()+" begins to feed on the "+
	corpse->short()+".\n");
    set_stuffed(query_stuffed() + 25);
    return 1;
}


/* TRACK FUNCTIONS */

/*
 * Function name: track_now
 * Description:   Actually perform the tracking
 * Arguments:     pl - the tracker
 *                skill - the tracking skill used
 */
void
track_now(object player, int track_skill)
{
    string *track_arr,
            result = "You do not find any tracks.\n",
            dir = "none",
           *dir_arr,
            race,
           *races = ({ "animal" });
    int     i;
    mixed  *exits;
    object room = environment(this_object());

    player = this_object();

    track_arr = room->query_prop(ROOM_S_DIR);

    track_skill /= 2;
    track_skill += random(track_skill);

    if (CAN_SEE_IN_ROOM(player) && pointerp(track_arr) && track_skill > 0)
    {
        dir = track_arr[0];
        if (dir == "X" || dir == "M")
            dir = "nowhere";
        if (strlen(dir)>5)
        {
            dir_arr = explode(dir," ");
            if (dir_arr[0] != "the")
            dir = "the " + dir;
        }
        race = track_arr[1];

        result = "You can make out some tracks on the ground.\n";

        switch(track_skill)
        {
            case  1..10:
                dir = "none";
                break;
            case 11..20:
                if(random(2))
                {
                    exits = room->query_exit();
                    if(i = sizeof(exits))
                        dir = exits[random(i/3)*3+1];
                }
                result += "They are probably leading towards " + dir + ".\n";
                break;
            case 21..50:
                result += "They are leading towards " + dir + ".\n";
                break;
            case 51..75:
                if(random(2))
                    race = races[random(sizeof(races))];
                result += "They were probably made by " +LANG_ADDART(race) +
                    " and are leading " + dir + ".\n";
                break;
            case 76..150:
                result += "They were made by " +LANG_ADDART(race) +
                    " and are leading " + dir + ".\n";
                break;
        }
    }

    player->query_leader()->remove_prop(LIVE_S_EXTRA_SHORT);
    tell_room(environment(player), QCTNAME(player) + " stops sniffing "+
	"the ground, "+(dir == "none" ? "but does not seem to have picked "+
	"up a scent." : "and points "+dir+" with "+POSSESSIVE(player)+
	" front paw.")+"\n", player, player);
    player->catch_msg(result);
    return;
}

/*
 * Function name: track_room
 * Description:   Someone looks for tracks in this room
 */
void
track_room()
{
    int     time,
            track_skill;
    object  paralyze;
    object  room = environment(this_object());

    time = room->query_prop(OBJ_I_SEARCH_TIME);
    if (time < 1)
        time = 10;
    else
        time += 5;

    track_skill = this_object()->query_skill(SS_TRACKING);
    time -= track_skill/10;

    if (time < 1)
        track_now(this_object(), track_skill);
    else
    {
        set_alarm(itof(time), 0.0, &track_now(this_object(), track_skill));

        seteuid(getuid());
        paralyze = clone_object("/std/paralyze");
        paralyze->set_standard_paralyze("tracking");
        paralyze->set_standard_paralyze("tracking");
        paralyze->set_stop_fun("stop_track");
        paralyze->set_stop_verb("stop");
        paralyze->set_stop_message("You stop searching for tracks.\n");
        paralyze->set_remove_time(time);
        paralyze->set_fail_message("You are busy searching for tracks. You "+
	    "must 'stop' to do something else.\n");
        paralyze->move(this_object(),1);
    }
}

/*
 * Function name: dtrack
 * Description:   have the dog look for tracks
 * Argument:      str - the string given to the command
 * Returns:       0 - failure
 */
int
dtrack(string str)
{
    object  room = environment(this_player());
    object me;

    NF("What?\n");
    if (MCREST->query_lord_status(TP->query_name()) < MERC_STATUS_ASPIRING &&
	!TP->query_wiz_level())
	return 0;

    if (TP->query_leading_mercdog() && 
        TP->query_mercdog_follow()[0]->query_merc_dog())
        me = TP->query_mercdog_follow()[0];

    if (me->query_merc_dog() && me->query_attack())
    {
        notify_fail("Your dog is fighting and cannot track!\n");
        return 0;
    }
    else if (this_player()->query_attack())
    {
        notify_fail("But you are in the middle of a fight!\n");
        return 0;
    }

    if (stringp(str) &&
        (str != "here"))
    {
        notify_fail("Track where?\n");
        return 0;
    }

    if (!room->query_prop(ROOM_I_IS))
    {
        notify_fail("You cannot look for tracks here!\n");
        return 0;
    }

    if (!me && room->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot look for tracks inside a room!\n");
        return 0;
    }

    if (me && (me->query_mana() < (2 * F_TRACK_MANA_COST)))
    {
        notify_fail("Your dog is too mentally exhausted to "+
	    "look for tracks.\n");
	return 0;
    }
    else if (!me && (this_player()->query_mana() < (2 * F_TRACK_MANA_COST)))
    {
        notify_fail("You are mentally too exhausted to look for tracks.\n");
        return 0;
    }

    if (me)
    {
        write("You motion for your "+me->short()+" to look for tracks. "+
	    C(PRONOUN(me))+" lowers "+POSSESSIVE(me)+" head and begins to "+
	    "sniff the ground.\n");
        say(QCTNAME(this_player())+ " motions at "+POSSESSIVE(TP)+" "+
	    me->short()+". The "+me->short()+" lowers "+POSSESSIVE(me)+
	    " head and begins sniffing the ground.\n");
        me->add_prop(LIVE_S_EXTRA_SHORT, ", sniffing the ground");
        me->add_mana(-F_TRACK_MANA_COST);
        me->track_room();
        return 1;
    }
    else
    {
    write("You kneel down to examine the ground closely, looking for "+
	"tracks.\n");
    say(QCTNAME(this_player()) + " kneels down to examine the ground "+
	"closely.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, ", kneeling on the ground");
    this_player()->add_mana(-F_TRACK_MANA_COST);

    room->track_room();
    return 1;
    }

    write("Something went wrong.\n");
    return 1;
}

/*
 * Function name: stop_track
 * Description:   interrupt tracking
 * Arguments:
 * Returns:
 */
varargs int
stop_track(mixed arg)
{
    if (!objectp(arg))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "track_now")
            {
                args = calls[i][4];
                if (args[0] == this_object())
                    remove_alarm(calls[i][0]);
            }
        }
    }

//    tell_room(environment(this_object()), QCTNAME(this_object())
//      + " stops sniffing for tracks.\n",this_object());
    this_object()->remove_prop(LIVE_S_EXTRA_SHORT);

    return 0;
}


/* MESSENGER FUNCTIONS */

public void
tell_can_see(object who, string text)
{
	int i, size;
	object *oblist;

	oblist = FILTER_PRESENT_LIVE(all_inventory(environment(who)));
	oblist -= ({ who });
	oblist = FILTER_PLAYERS(oblist);
	oblist = FILTER_IS_SEEN(who, oblist);

	for (i = 0, size = sizeof(oblist);i < size;i++)
	{
		oblist[i]->catch_msg(text);
	}
}

public void
do_it()
{
    attack_func(query_attack());
}

public void
attack_func(object ob)
{
    string *str;
    object leader_room, leader_object;

    if (query_leader() == ob)
    {
	write("The "+short()+" looks confused at your attack, and decides "+
	   "to run away.\n");
	tell_can_see(ob, "The "+short()+" looks confused at "+
	   QTNAME(ob)+"'s attack, and runs away.\n");
        do_unlead(ob, 1);
 
        if (ob->query_name() != query_owner())
   	    set_alarm(0.2, 0.0, &fly_to_owner());
           else
            set_alarm(0.3, 0.0, &remove_object());

        if (!query_prop(LIVE_I_DOG_ATTACKER))
 	    add_prop(LIVE_I_DOG_ATTACKER, ({ ob->query_name(), }));
        else
        {
            if (member_array(ob->query_name(), 
		query_prop(LIVE_I_DOG_ATTACKER)) == -1)
            {
                str = query_prop(LIVE_I_DOG_ATTACKER);
	        str += ({ ob->query_name() });
                add_prop(LIVE_I_DOG_ATTACKER, str);
            }
        }
	    
        return;
    }	

    leader_object = find_player(lower_case(query_owner()));

    if(objectp(leader_object))
        leader_room = environment(leader_object);

    if ((!query_leader() || query_leader()->query_name() != query_owner()) &&
	leader_room != environment(TO))
    {
        if (query_leader())
            do_unlead(query_leader(), 1);

	ob->catch_tell(capitalize(LANG_THESHORT(this_object())) + " growls "+
	    "fiercely at you and then runs away.\n");
	tell_can_see(ob, capitalize(LANG_ASHORT(this_object())) + 
		" growls fiercely at "+QTNAME(ob)+" and then runs away.\n");

	move(TEMP_ROOM, 1);

	set_alarm(DELAY, 0.0, &fly_to_owner());


        if (!query_prop(LIVE_I_DOG_ATTACKER))
 	    add_prop(LIVE_I_DOG_ATTACKER, ({ ob->query_name(), }));
        else
        {
            if (member_array(ob->query_name(), 
		query_prop(LIVE_I_DOG_ATTACKER)) == -1)
            {
                str = query_prop(LIVE_I_DOG_ATTACKER);
	        str += ({ ob->query_name() });
                add_prop(LIVE_I_DOG_ATTACKER, str);
            }
        }

    }
    else
    {
	ob->catch_tell(capitalize(LANG_THESHORT(this_object())) + " growls "+
	    "fiercely at you.\n");
	tell_can_see(ob, capitalize(LANG_ASHORT(this_object())) + 
		" growls fiercely at "+QTNAME(ob)+".\n");
        
        if (!query_prop(LIVE_I_DOG_ATTACKER))
 	    add_prop(LIVE_I_DOG_ATTACKER, ({ ob->query_name(), }));
        else
        {
            if (member_array(ob->query_name(), 
		query_prop(LIVE_I_DOG_ATTACKER)) == -1)
            {
                str = query_prop(LIVE_I_DOG_ATTACKER);
	        str += ({ ob->query_name() });
                add_prop(LIVE_I_DOG_ATTACKER, str);
            }
        }

    }

    return;
}

public void
attacked_by(object ob)
{
    set_alarm(0.2, 0.0, &attack_func(ob));

    ::attacked_by(ob);
}

public void
normal_receive_message(object who)
{
        if (C(gSender) == query_owner())
	{
	who->catch_tell(capitalize(LANG_ASHORT(this_object())) + 
		" comes pacing up to you with a scroll bearing a "+
		"crest of "+query_barding()+" tied to "+
		POSSESSIVE(TO)+" harness from " +
		capitalize(gSender) + ".\n");
	tell_can_see(who, capitalize(LANG_ASHORT(this_object())) + 
		" goes pacing up to " + QTNAME(who) + 
		" with a scroll bearing a crest of "+query_barding()+
		" tied to "+POSSESSIVE(TO)+" harness.\n");
        return;
        }

	who->catch_tell(capitalize(LANG_ASHORT(this_object())) + 
		" comes pacing up to you with a scroll tied to "+
		POSSESSIVE(TO)+" harness from " +
		capitalize(gSender) + ".\n");
	tell_can_see(who, capitalize(LANG_ASHORT(this_object())) + 
		" goes pacing up to " + QTNAME(who) + 
		" with a scroll tied to "+POSSESSIVE(TO)+" harness.\n");
}

public void
heavy_receive_message(object who)
{
	who->catch_tell("You hear your "+short()+" barking in the "+
	   "distance, and realize that "+query_pronoun()+" cannot get to "+
	    "you.\n");
        move(TEMP_ROOM, 1);
}

public void
failed_message()
{
	object sender = find_player(gSender);

	sender->catch_tell(capitalize(LANG_THESHORT(this_object())) + 
		" comes pacing up to you, with your scroll for " + 
		capitalize(gWho) + " still tied to "+POSSESSIVE(TO)+
		" harness.\n");
	tell_can_see(sender, capitalize(LANG_ASHORT(this_object())) + 
		" goes pacing up to " + QTNAME(sender) + 
		" with a scroll tied to "+POSSESSIVE(TO)+" harness.\n");
}

public void
normal_send_message()
{
	object sender = find_player(gSender);

        if (sender->query_name() == query_owner())
        {
	write("You roll up the scroll and seal it with your crest. You then "+
		"tie it to " +
		LANG_THESHORT(this_object()) + "'s harness, instructing " + 
		query_objective() + " to deliver it to " + 
		capitalize(gWho) + ". " + 
		capitalize(LANG_THESHORT(this_object())) + " runs off to "+
		"carry out your command.\n");
	tell_can_see(sender, QCTNAME(sender) + " rolls up a scroll and " +
		"seals it with "+POSSESSIVE(sender)+" crest of a "+
		query_barding()+". "+C(PRONOUN(TP))+" then "+
		"ties it to " + LANG_THESHORT(this_object()) + "'s "+
		"harness, motioning for "+LANG_THESHORT(TO)+" to go, "+
		"which "+PRONOUN(TO)+" does.\n");
	return;
        }	

	write("You roll up the scroll and tie it to " +
		LANG_THESHORT(this_object()) + "'s harness, instructing " + 
		query_objective() + " to deliver it to " + 
		capitalize(gWho) + ". " + 
		capitalize(LANG_THESHORT(this_object())) + " runs off to "+
		"carry out your command.\n");
	tell_can_see(sender, QCTNAME(sender) + " rolls up a scroll, " +
		"and ties it to " + LANG_THESHORT(this_object()) + "'s "+
		"harness, motioning for "+LANG_THESHORT(TO)+" to go, "+
		"which "+PRONOUN(TO)+" does.\n");
}

public void
deliver_message()
{
	object scroll;
	object sender = find_player(gSender);
	object who = find_player(gWho);

	/* Failed to find the player, or player is linkdead. */
	if (!objectp(who) ||
	  !interactive(who))
	{
		if (!objectp(sender))
		{
			return;
		}

                do_lead(sender);

		set_alarm(0.1, 0.0, &failed_message());

		/* Sender can't carry faerie, sent to faerie room */
		if (move(environment(sender)))
		{
                        if (query_leader())
                            do_unlead(query_leader(), 1);

			set_alarm(0.2, 0.0, &heavy_receive_message(who));
		}
	}
	else
	{
		set_alarm(0.1, 0.0, &normal_receive_message(who));
		scroll = clone_object(MESSAGE);
		scroll->set_message(gMessage);
		scroll->set_sender(gSender);

                if (C(gSender) == query_owner())
		    scroll->set_crest(query_barding());

		scroll->move(who, 1);
                
                do_lead(who);

		if (move(environment(who)))
		{
                        if (query_leader())
                            do_unlead(query_leader(), 1);

            	        who->catch_tell(capitalize(LANG_ASHORT(this_object())) + 
 		            " comes pacing up to you with a scroll tied to "+
		            POSSESSIVE(TO)+" harness from " +
		            capitalize(gSender) + ", before running away.\n");
	                tell_can_see(who, capitalize(LANG_ASHORT(this_object())) + 
		            " goes pacing up to " + QTNAME(who) + 
		            " with a scroll tied to "+POSSESSIVE(TO)+" harness, "+
			    "and then quickly runs away.\n");
			set_alarm(DELAY, 0.0, &fly_to_owner());
		}
	}
}

public int
edit_message(string message)
{
        if (this_player() != query_leader())
		return 0;

	if (!strlen(message))
	{
		write("You decide against sending a missive.\n");
		return 1;
	}

	gMessage = message;

	gSender = this_player()->query_real_name();
	set_alarm(0.1, 0.0, &normal_send_message());

        if (query_leader())
            do_unlead(query_leader(), 1);

	move(TEMP_ROOM, 1);
	set_alarm(DELAY, 0.0, &deliver_message());
	return 1;
}

private int
send_message(string str)
{
        if ((query_leader()->query_name() == query_owner() &&
	    query_verb() == "send") || (query_verb() == "dsend" &&
	    query_leader()->query_name() != query_owner()))
	    return 0;

        if (this_player() != query_leader())
		return 0;

	if (!strlen(str))
	{
		notify_fail("Send a message to whom?\n");
		return 0;
	}

	if (SECURITY->query_wiz_level(str) &&
	  !this_player()->query_wiz_level())
	{
		notify_fail(capitalize(LANG_THESHORT(this_object())) + 
			" refuses to disturb a wizard.\n");
		return 0;
	}
	else if (lower_case(str) == "reply" ||
	  lower_case(str) == "a reply")
	{
		if (stringp(gSender) &&
		  this_player()->query_real_name() != gSender &&
		  this_player()->query_real_name() == gWho)
		{
			str = gSender;
		}
		else
		{
			notify_fail("You have to have received a message " +
				"to send a reply.\n");
			return 0;
		}
	}

	write("You begin to jot down a message for " +
		capitalize(str) + ".\n");
	gWho = lower_case(str);
	clone_object(EDITOR_OBJECT)->edit(&edit_message());
	return 1;
}

public void
fly_to_owner()
{
	object owner = find_player(lower_case(query_owner()));

        string message = (capitalize(LANG_THESHORT(this_object())) + 
		" runs off into the distance.\n");

	if (objectp(environment(TO)))
	{
		if (IS_PLAYER_OBJECT(environment(TO)))
		{
			tell_room(environment(environment(TO)), message,
				environment(TO), this_object());
			environment(TO)->catch_tell(message);
		}
		if (IS_ROOM_OBJECT(environment(TO)))
		{
			tell_room(environment(TO), message, 0, this_object());
		}
	}
	if (objectp(owner))
	{
                if (query_leader())
                    do_unlead(query_leader(), 1);

                do_lead(owner);

		if (move(environment(owner)))
		{
                        if (query_leader())
                            do_unlead(query_leader(), 1);

			&heavy_receive_message(owner);
			return;
		}

		owner->catch_tell("Your "+this_object()->short() + 
			" comes pacing up to you, wagging "+POSSESSIVE(TO)+
			" tail.\n");
		tell_can_see(owner,
			capitalize(LANG_THESHORT(this_object())) + 
			" comes pacing up to "+QTNAME(owner)+", wagging "+
			POSSESSIVE(TO)+" tail.\n");
	}
	else
	{
                if (query_leader())
                    do_unlead(query_leader(), 1);

		set_alarm(0.1, 0.0, &remove_object());
		return;
	}
}

public void
fly_away()
{
	string message = (capitalize(LANG_THESHORT(this_object())) +
		" runs off into the distance.\n");

	if (IS_PLAYER_OBJECT(environment()))
	{
		tell_room(environment(environment()), message, 
			environment(), this_object());
		environment()->catch_tell(message);
	}
	if (IS_CORPSE_OBJECT(environment()))
	{
		tell_room(environment(environment()), message);
	}
	if (IS_ROOM_OBJECT(environment()))
	{
		tell_room(environment(), message, 0, this_object());
	}

        if (query_leader())
            do_unlead(query_leader(), 1);

	set_alarm(0.2, 0.0, &remove_object());
}

private int
return_faerie(string str)
{
	object owner = find_player(lower_case(query_owner()));
	object *faeries;

        if (!strlen(str))
	    str == "dog";

	faeries = FIND_STR_IN_OBJECT(str, environment(this_player()));

        if (this_player() != query_leader())
	    return 0;

	if (objectp(owner) && member_array(this_object(), faeries) != -1 && 
	    environment(owner) == environment(this_object()) &&
	    query_leader() != owner)
	{
		write("You send " + LANG_THESHORT(this_object()) + 
			" away. " + capitalize(LANG_THESHORT(this_object())) + 
			" turns and walks up to "+
			owner->query_the_name(this_player())+", wagging "+
			POSSESSIVE(TO)+" tail happily.\n");
		tell_room(E(this_player()), QCTNAME(this_player()) + 
			" sends " + LANG_ASHORT(this_object()) + " away. " + 
			capitalize(LANG_THESHORT(this_object())) + 
			" turns and walks up to "+QTNAME(owner)+", wagging "+
			POSSESSIVE(TO)+" tail happily.\n", ({ TP, owner}));
		owner->catch_tell(this_player()->query_The_name(owner) + 
			" sends " + LANG_ASHORT(this_object()) + " away. " + 
			capitalize(LANG_THESHORT(this_object())) + 
			" turns and walks up to you, wagging "+
			POSSESSIVE(TO)+" tail happily.\n");

               if (query_leader())
                   do_unlead(query_leader(), 1);

               do_lead(owner);
               return 1;
	}
	if (member_array(this_object(), faeries) != -1)
	{
		write("You send " + LANG_THESHORT(this_object()) + 
			" away. " + capitalize(LANG_THESHORT(this_object())) + 
			" runs off into the distance.\n");
		tell_can_see(this_player(), QCTNAME(this_player()) + 
			" sends " + LANG_ASHORT(this_object()) + " away. " + 
			capitalize(LANG_THESHORT(this_object())) + 
			" runs off into the distance.\n");
	}
	else
	{
		return 0;
	}

	if (!objectp(owner))
	{
                if (query_leader())
                    do_unlead(query_leader(), 1);

		set_alarm(0.1, 0.0, &remove_object());
	}
	else if (this_player()->query_name() == query_owner())
	{
                if (query_leader())
                    do_unlead(query_leader(), 1);

                MKENNEL->lord_returned_dog(TP->query_name());
		set_alarm(0.1, 0.0, &remove_object());
	}
	else
	{
               if (query_leader())
                   do_unlead(query_leader(), 1);

		move(TEMP_ROOM, 1);
		set_alarm(DELAY, 0.0, &fly_to_owner());
	}

	return 1;
}

private int
resend_message(string str)
{
        notify_fail("What?\n");
        if ((query_leader()->query_name() == query_owner() &&
	    query_verb() == "resend") || (query_verb() == "dresend" &&
	    query_leader()->query_name() != query_owner()))
	    return 0;

        if (query_leader()->query_name() != query_owner())
	    return 0;

	if (this_player()->query_name() == query_owner())
	{
                if (query_leader())
                    do_unlead(query_leader(), 1);

		set_alarm(0.1, 0.0, &normal_send_message());
		move(TEMP_ROOM, 1);
		set_alarm(DELAY, 0.0, &deliver_message());
		return 1;
	}
	else
	{
		notify_fail("You can't resend a message that you " +
			"haven't written yet.\n");
		return 0;
	}
}

/* Commands to stop a dog from fighting a player */
static void
remove_stop_dog_fighting_offer(object live, string str)
{
    mapping offers = live->query_prop(LIVE_M_STOP_FIGHTING);

    /* There is no mapping. */
    if (!mappingp(offers))
    {
        return;
    }

    /* The offer is still valid, do not touch. */
    if (offers[str] >= (time() - 10))
    {
        return;
    }

    /* Revoke the offer. */
    offers = m_delete(offers, str);
    if (m_sizeof(offers))
    {
        live->add_prop(LIVE_M_STOP_FIGHTING, offers);
    }
    else
    {
        live->remove_prop(LIVE_M_STOP_FIGHTING);
    }
}

public int
stop_fighting(string str)
{
    object *oblist;
    mapping offers;
    object me = TP;

    if (me->query_name() != query_owner())
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Command your dog to stop fighting whom?\n");
        return 0;
    }

    /* Player wants to stop fighting his current enemy. */
    if (str == "fighting")
    {
        oblist = ({ query_attack() });
        if (!objectp(oblist[0]))
        {
            notify_fail("Your dog is not fighting anyone.\n");
            return 0;
        }
    }
    else
    {
        oblist = parse_this(str, "[fighting] [the] %l");
        switch(sizeof(oblist))
        {
        case 0:
            notify_fail("Command your dog to stop fighting whom?\n");
            return 0;

        case 1:
            break;

        default:
            notify_fail("Command your dog to stop fighting one person "+
		"at a time, please?\n");
            return 0;
        }
    }

    /* See if someone offered to stop fighting us. This offer must be accepted
     * within 10 seconds after the offer was made.
     */
    offers = oblist[0]->query_prop(LIVE_M_STOP_FIGHTING);
    str = file_name(TO);
    if (mappingp(offers) &&
        (offers[str] >= (time() - 10)))
    {
        offers = m_delete(offers, str);
        if (m_sizeof(offers))
        {
            oblist[0]->add_prop(LIVE_M_STOP_FIGHTING, offers);
        }
        else
        {
            oblist[0]->remove_prop(LIVE_M_STOP_FIGHTING);
        }

        write("You shout a command to your "+short()+", and "+PRONOUN(TO)+
	    " backs away from "+oblist[0]->query_the_name(me)+
	    " obediently.\n");
        oblist[0]->catch_tell(me->query_The_name(oblist[0])+" shouts a "+
	    "command to the "+short()+", and "+PRONOUN(TO)+" backs away "+
	    "from you obediently.\n");
        say(QCTNAME(me) + " shouts a command to the "+short()+", and "+
	    PRONOUN(TO)+" backs away from "+QTNAME(oblist[0])+" obediently.\n", 
	    ({ this_player(), oblist[0] }));

        stop_fight(oblist[0]);
        oblist[0]->stop_fight(TO);
        return 1;
    }

    /* Before we offer, are we fighting him? */
    if (member_array(oblist[0], query_enemy(-1)) == -1)
    {
        write("Your dog is not fighting " +
            oblist[0]->query_the_name(this_player()) + ".\n");
        return 1;
    }

    offers = query_prop(LIVE_M_STOP_FIGHTING);
    str = file_name(oblist[0]);
    if (!mappingp(offers))
    {
        offers = ([ ]);
    }

    /* Offer to cease hostilities, or renew the offer. */
    if (!offers[str])
    {
        write("You shout a command to your "+short()+", and "+PRONOUN(TO)+
	    " backs away from "+oblist[0]->query_the_name(me)+" but continues to "+
	    "growl at "+OBJECTIVE(oblist[0])+".\n");
        oblist[0]->catch_tell(me->query_The_name(oblist[0]) +
            " shouts a command to the "+short()+", and "+PRONOUN(TO)+" backs "+
	    "away from you, giving you the " +
            "chance to stop fighting with " +
            OBJECTIVE(TO) + " if you so choose. To " +
            "accept this offer, you must indicate that you also wish to " +
            "stop fighting within a short period of time.\n");
        say(QCTNAME(me) + " shouts a command to the "+short()+", and "+
	    PRONOUN(TO)+" backs away from "+QTNAME(oblist[0])+" but "+
	    "continues to growl at "+OBJECTIVE(oblist[0])+".\n",
            ({ this_player(), oblist[0] }));
    }
    else
    {
        write("You shout a command to your "+short()+", and "+PRONOUN(TO)+
	    " again backs away from "+oblist[0]->query_the_name(me)+
	    ", continuing to "+
	    "growl at "+OBJECTIVE(oblist[0])+".\n");
        oblist[0]->catch_tell(me->query_The_name(oblist[0]) +
            " shouts a command to the "+short()+", and "+PRONOUN(TO)+"again "+
	    "backs away from you, giving you another " +
            "chance to stop fighting with " +
            OBJECTIVE(TO) + " if you so choose. To " +
            "accept this offer, you must indicate that you also wish to " +
            "stop fighting within a short period of time.\n");
        say(QCTNAME(me) + " shouts a command to the "+short()+", and "+
	    PRONOUN(TO)+" backs away from "+QTNAME(oblist[0])+" again but "+
	    "continues to growl at "+OBJECTIVE(oblist[0])+".\n",
            ({ this_player(), oblist[0] }));
    }

    /* Register the offer. */
    offers[str] = time();
    add_prop(LIVE_M_STOP_FIGHTING, offers);

    /* Purposely remove after 15 and not 10 seconds. */
    set_alarm(15.0, 0.0, &remove_stop_dog_fighting_offer(TO, str));

    /* Call the hook after all messages are printed. */
    oblist->hook_stop_fighting_offer(this_player());
    return 1;
}


/* The repeating do_agression function to have the dog continue
 * to dislike certain people :)
 */
public void do_aggression(object ob)
{
    string *attackers;
    string name = ob->query_name();
    int interval = 20 + random(20);  // average of 30 seconds

    if (E(ob) != E(TO) || !CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, ob))
    {
	agg = m_delete(agg, ob->query_name());
	return;
    }

    if (query_prop(LORD_SAID_HUSH))
    {
	remove_prop(LORD_SAID_HUSH);
	agg = ([ ]);
        return;
    }

    if (member_array(name, m_indexes(agg)) == -1)
	return;

    if (member_array(name, query_prop(LIVE_I_DOG_ATTACKER)) != -1)
    {
        if (time() > (agg[name][1] + ATTACKER_FORGIVE_TIME))
	{
	    agg = m_delete(agg, name);
	    return;
        }

        if (ob->query_prop(OBJ_I_HIDE))
            ob->reveal_me(1);

        agg[name][0] = agg[name][0] - 1;

        if (agg[name][0] > 0)
	{
	    switch(random(6))
	    {
		case 0:
		        tell_room(E(TO), "The "+short()+" growls menacingly "+
			"at "+QTNAME(ob)+", baring "+POSSESSIVE(TO)+" sharp "+
			"teeth in warning.\n", ob);
			ob->catch_tell("The "+short()+" growls menacingly at "+
			"you, baring "+POSSESSIVE(TO)+" sharp teeth in warning.\n");
			break;
		case 1:
			tell_room(E(TO), "The "+short()+" barks at "+QTNAME(ob)+
			" relentlessly.\n", ob);
			ob->catch_tell("The "+short()+" barks at you "+
			"relentlessly.\n");
			break;
		case 2:
			tell_room(E(TO), "The "+short()+" stares intently at "+
			QTNAME(ob)+", the hair on "+POSSESSIVE(TO)+" back "+
			" standing upright.\n", ob);
			ob->catch_tell("The "+short()+" stares intently at "+
			"you, the hair on "+POSSESSIVE(TO)+" back standing "+
			"upright.\n");
			break;
		case 3:
			tell_room(E(TO), "The "+short()+" bares "+POSSESSIVE(TO)+
			" teeth at "+QTNAME(ob)+" in warning.\n", ob);
			ob->catch_tell("The "+short()+" bares "+POSSESSIVE(TO)+
			" teeth at you in warning.\n");
			break;
		case 4:
			tell_room(E(TO), "The "+short()+" paces back and forth, "+
			"staring at "+ QTNAME(ob)+" intently.\n", ob);
			ob->catch_tell("The "+short()+" paces back and forth, "+
			"staring at you intently.\n");
			break;
		case 5:
			tell_room(E(TO), "The "+short()+" snaps "+POSSESSIVE(TO)+
			" jaw several times at "+QTNAME(ob)+", "+POSSESSIVE(TO)+
			" sharp teeth clicking with each snap.\n", ob);
			ob->catch_tell("The "+short()+" snaps "+POSSESSIVE(TO)+
			" jaw shut several times at you, and you can hear the "+
			"clicking of "+POSSESSIVE(TO)+" sharp teeth.\n");
			break;
	    }
        
         
	    set_alarm((itof(interval)), 0.0, &do_aggression(ob));
	}
        else if (agg[name][0] == 0)
        {
	    tell_room(E(TO), "The "+short()+" looks like "+PRONOUN(TO)+
		" has settled down and "+
		"is no longer aggressive towards "+QTNAME(ob)+".\n", ob);
	    ob->catch_tell("The "+short()+" looks like "+PRONOUN(TO)+" has "+
		"settled down and is no longer aggressive towards you.\n");

            attackers = query_prop(LIVE_I_DOG_ATTACKER);

	    if (member_array(name, attackers) != -1)
		attackers -= ({ name });

	    add_prop(LIVE_I_DOG_ATTACKER, attackers);

  	    agg = m_delete(agg, name);
	}

        return;
    }

    if (time() > (agg[name][1] + ATTACKER_FORGIVE_TIME))
    {
	agg = m_delete(agg, name);
	return;
    }

    if (ob->query_prop(OBJ_I_HIDE))
        ob->reveal_me(1);

    agg[name][0] = agg[name][0] - 1;

    if (agg[name][0] > 0)
    {
	switch(random(6))
	{
	    case 0:
	        tell_room(E(TO), "The "+short()+" sniffs around "+
		    QTNAME(ob)+".\n", ob);
                ob->catch_tell("The "+short()+" sniffs around you.\n");
		break;
	    case 1:
		tell_room(E(TO), "The "+short()+" barks at "+QTNAME(ob)+".\n",
			ob);
		ob->catch_tell("The "+short()+" barks at you!\n");
		break;
	    case 2:
		tell_room(E(TO), "The "+short()+" stares intently at "+
		    QTNAME(ob)+".\n", ob);
		ob->catch_tell("The "+short()+" stares intently at you.\n");
		break;
    	    case 3:
		tell_room(E(TO), "The "+short()+" whimpers as "+PRONOUN(TO)+
		    " looks at "+QTNAME(ob)+".\n", ob);
		ob->catch_tell("The "+short()+" whimpers as "+PRONOUN(TO)+
		    " looks at you.\n");
		break;
	    case 4:
		tell_room(E(TO), "The "+short()+" jumps around excitedly, "+
		   "looking at "+QTNAME(ob)+".\n", ob);
		ob->catch_tell("The "+short()+" jumps around excitedly, "+
		   "looking at you.\n");
		break;
	    case 5:
		tell_room(E(TO), "The "+short()+" sits down and stares at "+					QTNAME(ob)+".\n", ob);
		ob->catch_tell("The "+short()+" sits down and stares at you.\n");
		break;
	}
         
    set_alarm((itof(interval)), 0.0, &do_aggression(ob));
    }
    else if (agg[name][0] == 0)
    {
        tell_room(E(TO), "The "+short()+" looks like "+PRONOUN(TO)+
	    " has settled down and "+
	    "is no longer suspicious of "+QTNAME(ob)+".\n", ob);
	ob->catch_tell("The "+short()+" looks like "+PRONOUN(TO)+" has "+
	    "settled down and is no longer suspicious of you.\n");
	agg = m_delete(agg, name);
    }

    return;
}
    
void
do_alert_attacker(object ob)
{
    if (E(TO) != E(ob))
	return;

    if (ob->query_prop(OBJ_I_HIDE))
        ob->reveal_me(1);

    tell_room(E(TO), "The "+short()+" growls viciously, baring "+POSSESSIVE(TO)+
	" sharp teeth at "+QTNAME(ob)+".\n", ob);
    ob->catch_tell("The "+short()+" growls viciously at you, baring "+
	POSSESSIVE(TO)+" sharp teeth in warning.\n");
    return;
}

void
do_alert_hidden(object ob)
{
    if (E(TO) != E(ob))
	return;

    if (ob->query_prop(OBJ_I_HIDE))
        ob->reveal_me(1);

    tell_room(E(TO), "The "+short()+" suddenly stands at attention, ears "+
	"forward, and stares intently at "+QTNAME(ob)+".\n", ob);
    ob->catch_tell("The "+short()+" suddenly stands at attention, ears "+
	"forward, and stares intently at you!\n");
    return;
}

int do_hush(string str)
{
    NF("What?\n");
    if (TP->query_name() != query_owner())
        return 0;

    add_prop(LORD_SAID_HUSH, 1);

    write("You motion for your "+short()+" to be silent.\n");
    say(QCTNAME(TP)+" motions for the "+short()+" to be silent.\n");
    return 1;
}

/* Add a custom can_see because the mudlib one sucks */
public int custom_can_see(object me, object them)
{
    int hide = them->query_skill(SS_HIDE);
    int aware = query_skill(SS_AWARENESS);

    hide = hide - E(TO)->query_prop(ROOM_I_HIDE);

    /* By my calculation this gives a player with hide skill */
    /*   equal to the awareness skill a 50/50 chance of hiding */
    /*   rather than a 100% chance of failing, as the mudlib does */
    if (aware > ((hide * 3 / 4) + random((hide / 2))))
	return 1;

    return 0;
}

void check_invalid_dog(object own)
{
    if (!objectp(own) || 
	file_name(this_object()) != own->query_prop("_merc_lord_my_dog"))
    {
	tell_room(environment(this_object()),
	   "The "+short()+" paces off into the distance.\n");
	remove_object();
	return;
    }
}

public int
dog_command(string str)
{
    string *owner_commands = ({ "send", "resend", "return", "scavenge",
	"drink", "hush", "stopfight", "stay", "follow", "track" });
    string *other_commands = ({ "send", "resend", "return", "stay", 
	"follow" });
    string *tmp;

    notify_fail("Only the leader of the dogs may command them.\n");
    if (this_player() != query_leader() &&
	this_player()->query_name() != query_owner())
	return 0;

    if (query_leader()->query_name() == query_owner())
    notify_fail("Possible commands with dorder:\n"+
	"dorder send <name>      : send a missive to <name>\n"+
	"dorder resend <name>    : attempt to deliver again\n"+
	"dorder return           : return dog to kennel\n"+
	"dorder scavenge         : scavenge for food nearby\n"+
	"dorder drink            : drink from nearby water\n"+
	"dorder hush             : order dog to hush\n"+
	"dorder stopfight <name> : order dog to stop fighting <name>\n"+
	"dorder stay             : order dog to stay\n"+
	"dorder follow           : order dog to follow\n"+
	"dorder track            : order dog to track\n"+
	"Related commands:\n"+
	"dgagdog                 : do not see arrival messages\n"+
	"feed                    : feed your dog something\n");
    else
    notify_fail("Possible commands with dorder:\n"+
	"dorder send <name>      : send a missive to <name>\n"+
	"dorder resend <name>    : attempt to deliver again\n"+
	"dorder return           : return dog to kennel\n"+
	"dorder stay             : order dog to stay\n"+
	"dorder follow           : order dog to follow\n");
 
    if (!strlen(str))
	return 0;

    tmp = explode(str, " ");

    if (query_leader()->query_name() == query_owner())
    {
	if (member_array(tmp[0], owner_commands) == -1)
	    return 0;
    }
    else 
    {
        if (member_array(tmp[0], other_commands) == -1)
	    return 0;
    }

    if (sizeof(tmp) > 1)
	str = implode(tmp[1..(sizeof(tmp) - 1)], " ");
       else
	str = "";

    switch(tmp[0])
    {
	case "send":
		return send_message(str);
		break;
	case "resend":
		return resend_message(str);
		break;
	case "return":
		if (!strlen(str))
		    str = "dog";
		return return_faerie(str);
		break;
	case "scavenge":
		if (!strlen(str))
		    str = "here";
		return feed_horse(str);
		break;
	case "drink":
		return water_horse(str);
		break;
	case "hush":
		return do_hush(str);
		break;
	case "stopfight":
		return stop_fighting(str);
		break;
	case "stay":
		return leave_dog(str);
		break;
	case "follow":
                if (!strlen(str))
		    str = "dog";
		return lead_dog(str);
		break;
	case "track":
                if (!strlen(str))
		    str = "here";
		return dtrack(str);
		break;
    }

    return 0;
}


/* REDEFINITION OF move_living() AND do_die() AND leave_env() */

void
init_living()
{
    object ob = TP;
    object own;
    object *team;
    object lead;
    string *attackers;
    int aggression;
    int interval = 10 + random(20);

    ::init_living();

    add_action(dog_command, "dorder");
    add_action(feed, "feed");

    /* Make sure the dog has been configured before doing any of this */
    if (short() == "hunting messenger dog" || short() == "Dog")
        return;

    if (file_name(environment(this_object())) ==
        "/d/Genesis/guilds/me/room/dogs_temp")
    return;


    if (!objectp(own = find_living(lower_case(query_owner()))) ||
	file_name(this_object()) != own->query_prop("_merc_lord_my_dog"))
        set_alarm(1.0, 0.0, &check_invalid_dog(own));

    if (!query_leader() || query_leader()->query_name() != query_owner())
	return;

    if (!CAN_SEE_IN_ROOM(TO))
	return;

    if (!CAN_SEE(TO, ob) && !custom_can_see(TO, ob))
	return;

    /* React to attackers, even in the team of the owner */
    if (query_prop(LIVE_I_DOG_ATTACKER))
    {
        attackers = query_prop(LIVE_I_DOG_ATTACKER);

        if (member_array(ob->query_name(), attackers) != -1)
        {
            /* Bark for 5 - 15 minutes */
            aggression = 15 + random(30);

            if (member_array(ob->query_name(), m_indexes(agg)) == -1)
            {
                set_alarm((itof(interval)), 0.0, &do_aggression(ob));
	        agg += ([ ob->query_name() : ({ aggression, time() }) ]);
            }
            else if (agg[ob->query_name()][0] < aggression)
	        agg[ob->query_name()] = ({ aggression, time() });

	    set_alarm(1.0, 0.0, &do_alert_attacker(ob));
	    return;
        }
    }

    /* Do not react to sneakers in the team of the owner */
    if (objectp(lead = query_leader()->query_leader()))
    {
        if (lead == ob)
	return;

        if (member_array(ob, lead->query_team()) != -1)
	    return;
    }

    if (sizeof(team = query_leader()->query_team()))
        if (member_array(ob, team) != -1)
	    return;

    if (ob->query_prop(OBJ_I_HIDE))
    {
        /* Bark for 2 - 6 minutes */
        aggression = 6 + random(13);

        if (member_array(ob->query_name(), m_indexes(agg)) == -1)
        {
            set_alarm((itof(interval)), 0.0, &do_aggression(ob));
	    agg += ([ ob->query_name() : ({ aggression, time() }) ]);
	}
        else if (agg[ob->query_name()][0] < aggression)
	    agg[ob->query_name()] = ({ aggression, time() });

        set_alarm(1.0, 0.0, &do_alert_hidden(ob));

	return;
    }
}

void
do_die(object killer)
{
    string own = query_owner();

    if (query_hp() > 0)
      return;
    
    if (strlen(own))
    {
	MKENNEL->kill_lords_dog(own);
    }

    ::do_die(killer);
}

public void
leave_env(object from, object to)
{
	::leave_env(from, to);

	if (to->id("corpse"))
	{
		set_alarm(1.0, 0.0, &fly_away());
	}

        if (!objectp(from))
            return;

        if (file_name(from) == (MROOM + "dog_temp") &&
          gAlarmId > 0)
        {
            remove_alarm(gAlarmId);
        }
}

