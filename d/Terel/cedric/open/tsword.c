inherit "/std/weapon.c";
#include "/d/Terel/common/terel_std_rec.h"
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/ss_types.h"

#define BS(message) 	break_string(message,70)
#define PS(message)	process_string(message)
#define TP              this_player
#define TO              this_object

int	tried_to_drop_flag;

int
query_value()
{
    return 0;
}

int
query_weight()
{
    return 1000;
}

int
try_hit(object ob)
{
    if (present("thane_dark_one", environment(query_wielded()))) 
   	return 1;
   
    query_wielded()->catch_msg(BS("You prepare to strike with the ancient sword, when, like a "
	    + "faint echo, you hear a voice in the back of your mind: 'Mine "
	    + "is not to be wielded against this unworthy opponent. Till the "
	    + "fabric of time itself is torn, only the "
	    + "Darkest is to be cleaved by my blade...'  The echo dies and "
	    + "your hand drops from the hilt of the sword.\n"));
    query_wielded()->command("unwield thane_quest_sword");
    return -1;
}

void
init()
{
    ::init();
    add_action("catch_sell", "sell");
    add_action("catch_drop", "drop");
    add_action("catch_rread", "read");
}

string
catch_give()
{   
    return BS("As if from a great distance, you hear the ancient sword itself speak to "
	    + "you: 'When you took me in hand, you obliged yourself to a great Purpose; "
	    + "none can take your place. Drop me, if you feel you must, and I shall "
	    + " release you from my ageless quest.'\n");
}

void
create_weapon()
{
	tried_to_drop_flag = 0;
	set_name("sword");
	add_name("thane_quest_sword");
	add_name("LightBringer");
	add_name("lightbringer");
	set_short("ancient sword");
	set_adj("ancient");
	set_long("@@glow_func");
	set_hit(100);		/* only to be used against the Dark One */
	set_pen(100);		/* (see below)				*/

	set_wt(W_SWORD);
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_ANYH);

	add_prop("mystic_weapon",1);  /* allow mystics to use this sword */
}

string 
glow_func()
{
    string	*player_loc, *temp;
    string	str;
    int	i, light_val;
	
    light_val = 0;
    player_loc = explode(file_name(environment(TP())), "/");
    for (i=0;i<sizeof(player_loc);i++)
	if (member_array(player_loc[i], ({"Terel", "common", "town", "man", "tapestry_room", "battle_field"}))!=-1)
	    light_val++;
    switch (light_val)
	{
	    case 0: str= "glows very, very faintly"; break;
	    case 1: str= "glows faintly"; break;
	    case 2: str= "glows brightly"; break;
	    case 3: str= "shines with an inner light"; break;
	    case 4: str= "shines with a dazzling glare"; break;
	    case 5: str= "burns with a holy brilliance"; break;
	    case 6: str= "burns with the power of its makers"; break;
	}
    return BS("This mighty sword might have been forged "
	+ "in the fires of the sun itself. The blade, beautifully formed of a metal unknown to "
	+ "you, is inlaid with runes of mithril, and in the hilt a pure white "
	+ "stone "+str+". The sword is ancient; though the untarnished blade "
	+ "sparkles as though it were tempered yesterday, you feel its great age "
	+ "resonating somewhere deep within your very soul.\n");
}

int
catch_rread(string str)
{
    if (str!="runes") return 0;
    
    /* Check language skill. High enough, should read ancient elven runes
     * about origin and purpose of sword. Lower,  should identify runes 
     * as Elven. Lower,  no clue.
     */
    if (TP()->query_skill(SS_LANGUAGE)>40)
    {
	TO()->set_short("ancient sword named LightBringer");
	write("You recognize the runes as ancient Elvish. Studying them \n"
	+ "carefully, you make out an inscription:\n"
	+ "	We, who have forseen your need, do forge this blade in the\n"
	+ "	heat of truth and the fire of justice. Hither do we christen \n"
	+ "	it LightBringer. May it serve you well in the time of darkness,\n"
	+ "	and strike down the One who is most Dark. Wield it with \n"
	+ "	discrimination, for only in the presence of the Dark One shall\n"
	+ "	LightBringer fulfill its noble purpose.\n");
	return 1;
    }
    if (TP()->query_skill(SS_LANGUAGE)>15)
    {
	TO()->set_short("ancient sword, engraved with Elvish runes");
	write(BS("You recognize the runes as ancient Elvish, but your study "
	+ "of languages has not progressed far enough to let you read them.\n"));
	return 1;
    }
    write(BS("The runes are beautiful and complex, but you have no idea what "
    + "they say or even what language they might be in.\n"));
    return 1;
}

int
catch_sell(string str)
{
    object  ob;
    
    if (parse_command(str, TP(), "%o", ob) || str=="all" || str=="all!")
	if (ob == TO() || str=="all" || str=="all!")
	    if (ob == TO())
	    {
		write(BS("A voice sounds in your mind, as if from a great distance: "
		+ "Mine is not to be bought or sold; profit is no part of my Purpose.\n"));
		return 1;
	    }
}

void
do_flame()
{
    write("The ancient sword bursts into flames!\n");
    say("The ancient sword bursts into flames!\n");
    call_out("do_consume", 2);  
}

void
do_consume()
{
    write("The ancient sword is rapidly consumed.\n");
    say("The ancient sword is rapidly consumed.\n");
    TO()->remove_object();
}

int
catch_drop(string str)
{
    object  ob;
    
    if (parse_command(str, TP(), "%o", ob) || str=="all" || str=="all!")
	if (ob == TO() || str=="all" || str=="all!")
	    if (tried_to_drop_flag==1)
	    {
		say(BS(QCTNAME(TP())+" drops an ancient sword.\n"));
		call_out("do_flame", 4);
		write(BS("As you cast the sword upon the ground, you hear within "
		+ "your mind a faint echo: 'Perhaps you are not "+TP()->query_pronoun()
		+ " whom I have so long sought, then. Fare thee well, traveler!'\n"));
		TO()->move(environment(TP()));
		return 1;
	    }
	    else
	    {
		tried_to_drop_flag = 1;
		write(BS("A thought sounds in the back of your mind, almost as if it "
		+ "were your own: 'Drop me and I shall return to the place from whence "
		+ "I came. You have been warned.'\n"));
		return 1;
	    }
}

string
sword_catch_give()
{
    return BS("As if from a great distance, you hear the ancient sword itself speak to "
	    + "you: 'When you took me in hand, you obliged yourself to a great Purpose; "
	    + "none can take your place. Drop me, if you feel you must, and I shall "
	    + " release you from my ageless quest.'\n");
}
#include "/d/Terel/common/terel_defs.h"
