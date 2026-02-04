/*
 * Regata's black cat, by Udana,
 * Ripedoff from:
 * pfox.c
 *
 * Janus 920701
 * modified by Sorgum 941002
 * modified by Tomas for use with the Elderwood Forest. June 2000
 * remodified by Pasqua.. changing 25 to 26 in the cryptaid part
 */

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <stdproperties.h>

inherit STDMONSTER;
inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>

void lecture1();
void lecture2();
void lecture3();


/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    if (!IS_CLONE)
        return;

    ::create_creature();
    add_name("cesar");
    set_short("black cat");
    set_long("A large black cat.\n");
    set_adj(({"black"}));
    set_race_name("cat");
    set_alignment(-600);
    set_stats(({9, 10, 9, 5, 5, 15}));
    PASSIVE;
    set_act_time(11);
    add_act(({"emote meows.", "emote stares at you.", "yawn"}));
    SET_MAX_HP;
    set_gender(0);
    set_skill(SS_DEFENCE, random(5) + 25);
    add_prop(OBJ_I_WEIGHT, 22000);
    add_prop(OBJ_I_VOLUME, 22400);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    ADDSKIN;
    ADDMEAT(2);
    add_ask( ({"code", "password", "encryption"}), VBFC_ME("hint_password"), 1);
    add_ask( ({"help", "aid", "secret word"}), "say Yes, I think I can help you, you're trying to break bandits code, "+
	"aren't you?", 1);
}

string hint_password()
{
	command("say Oh, you mean the encryption system I invented couple years ago? Yes, I heard "+
		"local bandits are using it.");
	command("say To decode it you'll need an encryption key and a password. The password you'll "+
		"probably find on one of those bandits, a leader I would guess.\n");
	command("say As for the encryption key, I heard they have it scraped on a tree, or "+
		"a rock somewhere in the forest.\n");
	command("say When you have those, there are three simple things you need to do..");
	set_alarm(10.0, 0.0, &lecture1());
	return "";
}

/*The lecture continues */
void lecture1()
{
 command("say First change all the letters in password and key into numbers - 'a' is 0,'b' is 1, "+
              "and so on until 'z' which is 25. Now you have two series of numbers.");
 set_alarm(10.0, 0.0, &lecture2());
}

void lecture2()
{
 command("say Now increase every number in the password series by the corresponding number from key "+
              "series. When you reach the end of the key just start over - until every number in "+
              "password is changed.");
 set_alarm(10.0, 0.0, &lecture3());              
}

void lecture3()
{
 command("say The last things you need to do is change the numbers back into letters. You do it "+
              "just like you've changed them into numbers in the first place. Only when you "+
              "encounter a number bigger then 25 you need to substract 26 from it, "+
              "so it has a corresponding letter in the alphabet.");
}


#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(10, 5, W_SLASH,    70, A_BITE);
    add_attack(6,  3, W_BLUDGEON, 15, A_RPAW);
    add_attack(6,  3, W_BLUDGEON, 15, A_LPAW);

    add_hitloc( ({ 1, 1, 1 }), 10, "head", H_HEAD);
    add_hitloc( ({ 2, 2, 2 }), 50, "body", H_BODY);
    add_hitloc( ({ 2, 2, 2 }), 20, "legs", H_LEGS);
    add_hitloc( ({ 6, 6, 6 }), 30, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
     case A_BITE: return "bite";
     case A_RPAW: return "right front paw";
     case A_LPAW: return "left front paw";
    }
}
