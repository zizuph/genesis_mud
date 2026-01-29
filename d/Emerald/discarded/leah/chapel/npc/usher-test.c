/* chapel/npc/usher.c is cloned by chapel/chapel.c */
inherit "/std/monster";
 
#include "../chapel.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define THROWEE_BRIDE this_player()->query_prop(IS_BRIDE)
#define THROWEE_GROOM this_player()->query_prop(IS_GROOM)
#define THROWEE_MC present("_emerald_chapel_mc_wand", this_player())
 
#define EXIT    CHAPEL_DIR + "outside"

/* Prototypes */
int not_allowed(string arg);
int gob_allowed(string arg);
int kill(string str);

 
create_monster()
{ 
    set_name("usher");
    set_adj("big");
    add_adj("large");
    set_race_name("human");
    set_short("large usher");
    set_long("This usher is here to make sure that "+
       "there is no interruptions during the ceremony.\n");
 
    set_stats(({ 150, 150, 150, 150, 150, 150 }));
 
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
 
    set_hp(query_max_hp());
 
    set_alignment(50);
 
    add_prop(OBJ_I_WEIGHT, 91000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
}
 
void
arm_me()
{
    clone_object(CHAPEL_DIR + "arm/tux")->move(TO,1);
    clone_object(CHAPEL_DIR + "wep/shatter")->move(TO,1);
    command("wear all");
}
 
void
attacked_by(object ob)
{
  /* we go ahead and DO NOT finish attacked_by because it wierds */
  /* out with 'add action by object not present'. This shouldnt */
  /* be a problem, because if a player is kicked out, they shouldnt */
  /* be able to get back to the usher again without quitting out */
    int times;
 
    times = ob->query_prop(THROWN_OUT);

    /* Enough of the THROWN_OUT prop that they arent getting back in */
    ob->add_prop(THROWN_OUT, 3 - times );
    if(ob->query_prop(IS_BRIDE))
       {
	command("say to "+ob->query_real_name()+" Sorry lass...no "+
		"wedding...and no refunds!\n");
       }
    if(ob->query_prop(IS_GROOM))
       {
	command("say to "+ob->query_real_name()+" Sorry lad...no "+
		"wedding...and no refunds!\n");
       }
    if(present("_emerald_chapel_mc_wand", ob))
       {
	command("say to "+ob->query_real_name()+" You had to ruin a "+
		"perfectly good wedding. Have fun explaining to "+
		"the bride and groom that we don't give refunds!\n");
       }
    ob->catch_msg("You are violently ejected from the chapel by the furious "+
	 "usher!\n");
    tell_room(EXIT, QCTNAME(ob) + " is violently thrown out of the chapel "+
	"by a furious usher!\n");
    ob->move_living("M", EXIT);
    tell_room(environment(), QCTNAME(ob) + " is violently thrown out of "+
	"the chapel!\n");
}
 
void
help_me(object ob)
{
    command("wield sword");
    attack_object(ob);
}
 
void
init_living()
{
    ::init_living();    
    add_action(kill, "kill");

/* Allowed for goblin characters */
    add_action(gob_allowed, "shout");
    add_action(gob_allowed, "ack");
    add_action(gob_allowed, "choke");
    add_action(gob_allowed, "complain");
    add_action(gob_allowed, "confuse");
    add_action(gob_allowed, "confused");
    add_action(gob_allowed, "cough");
    add_action(gob_allowed, "cringe");
    add_action(gob_allowed, "despair");
    add_action(gob_allowed, "duh");
    add_action(gob_allowed, "eeks");
    add_action(gob_allowed, "fume");
    add_action(gob_allowed, "growl");
    add_action(gob_allowed, "hiccup");
    add_action(gob_allowed, "jump");
    add_action(gob_allowed, "moan");
    add_action(gob_allowed, "oops");
    add_action(gob_allowed, "poke");
    add_action(gob_allowed, "pout");
    add_action(gob_allowed, "shiver");
    add_action(gob_allowed, "snap");
    add_action(gob_allowed, "snarl");
    add_action(gob_allowed, "smirk");
    add_action(gob_allowed, "snore");
    add_action(gob_allowed, "startle");
    add_action(gob_allowed, "stretch");
    add_action(gob_allowed, "sulk");
    add_action(gob_allowed, "tickle");
    add_action(gob_allowed, "twiddle");
    add_action(gob_allowed, "whine");
    add_action(gob_allowed, "whistle");
    add_action(gob_allowed, "wiggle");
    add_action(gob_allowed, "yawn");
    add_action(gob_allowed, "yodel");

/* Not allowed for anyone */
    /*add_action(not_allowed, "burp"); commented out because of zodiac gem*/
    add_action(not_allowed, "puke");
    add_action(not_allowed, "steam");
    add_action(not_allowed, "stomp");
    add_action(not_allowed, "kick");
    add_action(not_allowed, "pounce");
    add_action(not_allowed, "tackle");
    add_action(not_allowed, "knee");
    add_action(not_allowed, "spit");
    add_action(not_allowed, "slap");
    add_action(not_allowed, "explode");
    add_action(not_allowed, "grope");
    add_action(not_allowed, "fart");
    add_action(not_allowed, "scream");
    add_action(not_allowed, "finger");
    add_action(not_allowed, "swear");
}
 
void
throw_out(object ob)
{
    int times;
 
    times = ob->query_prop(THROWN_OUT);
    ob->add_prop(THROWN_OUT, times + 1);
    ob->catch_msg("You are ejected from the chapel by the usher.\n");
    tell_room(EXIT, QCTNAME(ob) + " is thrown out of the chapel by an usher!\n");
    ob->move_living("M", EXIT);
    tell_room(environment(), QCTNAME(ob) + " is thrown out of the chapel!\n");
}
 
void
chastise(object ob)
{
	object *other_people;
	int i;
 
	ob->catch_msg("The usher leans over to you and whispers:\n\"I would have "+
		"thrown one of your guests out for that impoliteness.\"\n");

    other_people = FILTER_OTHER_LIVE(all_inventory(environment()));

    for (i=0 ; i<sizeof(other_people) ; i++)
        if (other_people[i]->id(ob))
			return;
		else
		other_people[i]->catch_msg("The usher leans over to " + QCTNAME(ob) +
			" and whispers something in " + ob->query_possessive() +
			" ear.\n");
}

void
ignore_me(object ob)
{
	object *other_people;
	int i;

	ob->catch_msg("The usher looks at you with utter disdain in his eyes.\n");

    other_people = FILTER_OTHER_LIVE(all_inventory(environment()));

    for (i=0 ; i<sizeof(other_people) ; i++)
        if (other_people[i]->id(ob))
			return;
		else
		other_people[i]->catch_msg("The usher looks at " + QCTNAME(ob) +
			" with utter disdain in his eyes.\n");
}

goblin_walkout()
{
	tell_room(environment(), "The usher looks around, mutters something "+
		"about not being paid enough to deal with goblins, and leaves.\n");
	remove_object(this_object());
}

int
kill(string str)
 {
    if(str!="usher" && str!="large usher") {
        throw_out(this_player());
        return 1;
    }
    return 0;
}
 
int
not_allowed(string str)
{
	if( THROWEE_BRIDE || THROWEE_GROOM || THROWEE_MC )
	{
		if( this_player()->query_race_name() == "goblin" )
		{
			goblin_walkout();
			return 1;
		}
		chastise(this_player());
		return 1;
	}
    throw_out(this_player());
    return 1;
}
 
int
gob_allowed(string str)
{
	if( THROWEE_BRIDE || THROWEE_GROOM || THROWEE_MC )
	{
		if( this_player()->query_race_name() == "goblin" )
		{
			goblin_walkout();
			return 1;
		}
		chastise(this_player());
		return 1;
	}
	if( this_player()->query_race_name() == "goblin" )
	{
		ignore_me(this_player());
		return 1;
	}
    throw_out(this_player());
    return 1;
}
