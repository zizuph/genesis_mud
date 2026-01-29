/*
 * AoB changes:
 *
 * 2019-04-28: Carnak
 *    This axe has proven to be far too unbalanced, if this is passed to someone
 *    who does not have axe skill to recharge, this axe can be used as an
 *    endless heal for a team tank.
 *
 *    The axe now drains ~1/3 of the players remaining health when failing to
 *    wield it. The recharge process cannot occur more than once every 2 
 *    minutes. It is capped at 1500 health and drains 1/5 of the amount healed
 *    as mana. There is a 3 second delay on the heal and it will be aborted if
 *    the axe is unwielded. You can now die from the health drain again, this is
 *    unlikely to instant-kill newbies as it is a base value of 50 + 1/3 of the
 *    remaining health of the player.
 *
 *    The starting restorable health is now 1000 and it is capped at 1500 as it
 *    was previous to this change.
 *
 * 2022-02-06: Ckrik
 *    This axe was made into a spell enhancer of power 42, death, fire and earth.
 *
 */
inherit "/d/Kalad/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
#include "/d/Kalad/defs.h"
#include <tasks.h>

// Global variables
static int      gHealthAmount   = 1000;
static mapping  gWieldAttempts  = ([]),
                gBloodyAlarms   = ([]);

// Prototypes
void remove_wounds(int amount);

/* by Antharanos */
void
create_weapon()
{
	::create_weapon();
	set_name("axe");
	set_adj("bloody");
	add_adj("steel");
	set_pname("axes");
	set_short("bloody steel axe");
	set_pshort("bloody steel axes");
	set_long("@@my_long");
	add_item(({"cryptic runes","runes","rune"}),
	"The eerily fluid shape of the runes seems to play tricks "+
	"upon your mind, forcing you to look away from them.\n");
	set_hit(42);
	set_pen(45);
	set_hands(W_ANYH);
	set_wt(W_AXE);
	set_dt(W_SLASH | W_IMPALE);
	set_wf(TO);
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(42);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_LIFE,
        SS_ELEMENT_FIRE, SS_ELEMENT_EARTH
    }));
    // add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(20) -10);
    // add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE) +;random(50) - 25)
	 add_prop(OBJ_I_VALUE,2000);
	 add_prop(OBJ_I_WEIGHT,20000);
	add_prop(OBJ_I_VOLUME,20000);
	add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
	add_prop(OBJ_S_WIZINFO,"This axe has been enchanted so "+
	"that it has a better hit and pen than normal weapons. "+
	"To wield the axe, the wielder must have > 100 str, "+
	"> 100 dis, 60 or better in the axe skill and 20 or better "+
	"in the spellcraft skill. In addition, because of its large "+
	"size, no hobbits may wield it. The axe can be commanded to "+
	"expend a portion of its power to heal its possesor. By "+
	"typing the command word, the wielder will be healed physically. "+
	"The axe initially has three charges of healing power, however, "+
	"whenever anyone tries to wield it and fails, the axe siphons "+
	"off that power and converts it into a charge. This weapon can "+
	"be found on Goliath "+
	"/d/Kalad/common/wild/pass/citadel/npc/goliath).\n");
	
	add_prop(MAGIC_AM_ID_INFO,({
    "The axe is magically enchanted. Those versed in magic may find the axe " +
    "useful in channeling arcane energy.\n", 5,
	"The axe has been magically enchanted to hit and penetrate more.\n", 25,
	"The enchanted axe has greater hit and penetration than normal "+
	"weapons and has several unique abilities. Failure to wield it will "+
	"result in bodily harm.\n", 55}));
	add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
	add_prop(OBJ_M_NO_BUY,1);
}

string
my_long()
{
	string empty_desc;
    
    switch(gHealthAmount)
    {
        case 1..500:
        empty_desc = "A dull red glow emanates from them.";
            break;
        case 501..1000:
        empty_desc = "A red glow shines from them.";
            break;
        case 1001..1500:
        empty_desc = "A fierce crimson color shines from them.";
            break;
        default:
        empty_desc = "Nothing emanates from them. They are more black than "
        + "red.";
            break;
    }
    
	return("A massive steel axe that is completely covered with dark, "+
      "red blood. Several cryptic runes have been etched in blood on its "+
      "pommel. " + empty_desc + "\n");
}

mixed
wield(object what)
{
    int health;
    
    if (this_player()->query_npc())
        return 0;
    
    foreach(string key, int value: gBloodyAlarms) remove_alarm(value);
    
    /* we will stop newbies to try to wield it */
    if (TP->query_base_stat(SS_STR) < 35)
    {
        write("You try to lift the " + short() + " enough to wield it, but "
        + "fail!\n");
        say(QCTNAME(TP)+" tries to lift the " + short() + " high enough to "
        + "wield it, but fails!\n");
        return "The " + short() + " is too heavy!\n";
    }

    if (TP->resolve_task(TASK_DIFFICULT, ({ TS_STR, TS_DIS })) > 0
        && TP->query_skill(SS_WEP_AXE) > 59
        && TP->query_skill(SS_SPELLCRAFT) > 19
		&& TP->query_race_name() != "hobbit")
    {
		write("Straining your entire body and mind to the limit, you barely "
        + "manage to gain control of the " + short() + ". A presence from "
        + "within it seems to have accepted you as its new owner.\n");
        say(QCTNAME(TP) + " breaks out into a sweat as " + TP->query_pronoun()
        + " attempts to gain control of the " + short() + ".\n");
        gBloodyAlarms["axe"] = set_alarm(10.0,0.0,"axe");
        return 0;
    }
    
    health = 50 + (this_player()->query_hp() / 3);
    
    write("You strain with all your might but are simply not worthy enough. A "
    + "presence from within the " + short() + " rejects you as a possible "
    + "owner.\n");
    
    if (gHealthAmount + health > 1500)
        health = 1500 - gHealthAmount;
    
    /* We dont want the axe to be recharged too fast */
    if (!health || time() - gWieldAttempts[this_player()] < 120)
        return "";
    
    gHealthAmount += health;
    
    say("A portion of " + QCTNAME(TP) + "'s life-force is drained by the "
    + short() + "!\n");
    this_player()->heal_hp(-health);
    
    if (this_player()->query_hp() <= 0)
        this_player()->do_die(this_object());
    
    return "A portion of your life-force was drained by the " + short() + "!\n";
}

int
axe(object ob)
{
    write("The presence within the " + short() + " urges you to feed it some "
    + "blood.\n");
    say(QCTNAME(TP) + " stares into space with a blank expression.\n");
    TP->command("$shout I hate Hobbits!!!");
    TP->command("$spit");
    TP->catch_msg("You try to kill the nearest hobbit!\n");
    TP->command("$kill hobbit");
    TP->catch_msg("You despise hobbits!\n");
    TP->command("$kill hobbit");
    gBloodyAlarms["fortify"] = set_alarm(10.0,0.0,"fortify");
    return 1;
}

mixed
unwield(object what)
{
    if (gBloodyAlarms["wound"])
    {
        this_player()->catch_msg("The surging power of the " + short()
        + " fades away.\n");
        remove_alarm(gBloodyAlarms["wound"]);
    }
    
    if (gBloodyAlarms["axe"])
        remove_alarm(gBloodyAlarms["axe"]);
    
    return 0;
}

init()
{
    ::init();
    add_action("wipe","wipe");
    add_action("impress","impress");
    add_action("shave","shave");
    add_action("axelick","axelick");
    add_action("fortify","fortify");
    add_action("command","command");
}

int
wipe()
{
    if (!TO->query_wielded())
    {
        write("You must wield the " + short() + " first.\n");
        return 1;
    }
    
    write("You wipe some of the dry, flaky blood of the " + short() + " onto "
    + "the ground.\n");
    say(QCTNAME(TP) + " wipes some of the dry, flaky blood of the " + short()
    + " onto the ground.\n");
    TP->command("grin devil");
    return 1;
}

int
impress()
{
    if (!TO->query_wielded())
    {
        write("You must wield the " + short() + " first.\n");
        return 1;
    }
    
    write("You skillfully spin the " + short() + " from one hand to the other "
    + "and then cut a massive swath through the air before you! Quite "
    + "impressive!\n");
    say(QCTNAME(TP) + " skillfully spins the " + short() + " from one hand to "
    + "the other then " + TP->query_pronoun() + " cuts a massive swath through "
    + "the air! Quite impressive!\n");
    TP->command("cackle");
    return 1;
}

int
shave()
{
    if (!TO->query_wielded())
    {
        write("You must wield the " + short() + " first.\n");
        return 1;
    }
    
    write("With surgeon-like precision, you carefully trim your whiskers.\n");
    say("With surgeon-like precision, " + QCTNAME(TP) + " carefully trims "
    + TP->query_possessive() + " whiskers.\n");
    TP->command("smile");
    return 1;
}

int
axelick()
{
    if (!TO->query_wielded())
    {
        write("You must wield the " + short() + " first.\n");
        return 1;
    }
    
    write("You slowly lick some of the blood from the " + short() + ", an "
    + "unstable glint flashing in your eyes.\n");
    say(QCTNAME(TP) + " slowly licks some of the blood from the " + short()
    + ", an unstable glint in " + TP->query_possessive() + " eyes.\n");
    TP->command("grin dem");
    return 1;
}

int
fortify()
{
    if (!TO->query_wielded())
    {
        write("The presence from within the " + short() + " urges you to wield "
        + "it.\n");
        return 1;
    }
    
    write("You feel power flow from within the " + short() + " to fortify you "
    + "against any obstacle.\n");
    say(QCTNAME(TP) + " grasps the " + short() + " closely and looks fortified "
    + "against any obstacle.\n");
    TP->command("smile confid");
    return 1;
}

int
command(string s)
{
    int lost_hp;
    
    if (!TO->query_wielded())
    {
        write("You must wield the " + short() + " first.\n");
        return 1;
    }
    
    NF(query_verb() + " what?\n");
    if (!s || s != "alrandulgur")
        return 0;

    NF("You call upon the power of the " + short() + ", but nothing occurs.\n");
    if (!gHealthAmount)
    {
        set_alarm(2.0,0.0,"destroy_axe",TP);
        return 0;
    }

    lost_hp = this_player()->query_max_hp() - this_player()->query_hp();
    
    if (lost_hp < 1)
        return 0;
    
    write("You call upon the power of the " + short() + ".\n");
    gBloodyAlarms["wound"] = set_alarm(3.0,0.0, &remove_wounds(lost_hp));
    return 1;
}

void
remove_wounds(int amount)
{
    if (gHealthAmount < amount)
        amount = gHealthAmount;
    
    gHealthAmount -= amount;
    this_player()->heal_hp(amount);
    this_player()->add_mana(-(amount / 5));
    
    gBloodyAlarms["wound"] = 0;
    
    write("The power of the " + short() + " flows into you!\n");
    write("You feel your health rising.\n");
    say(QCTNAME(TP) + " calls upon the power of the " + short() + ".\n");
    say(QCTNAME(TP) + " appears healthier!\n");
}

void
destroy_axe(object player)
{
    if (E(TO) == player)
    {
        write("Suddenly the " + short() + " turns into dust in your hands!\n");
        say("Suddenly the " + short() + " held by " + QTNAME(player) + " turns "
        + "into dust!\n");
        TO->remove_object();
        return;
    }
    
    tell_room(E(TO),"Suddenly the " + short() + " turns into dust!\n");
    TO->remove_object();
    return;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
