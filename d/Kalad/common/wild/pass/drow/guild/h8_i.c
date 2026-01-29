inherit "/std/object";
inherit "/cmd/std/command_driver.c";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/drow/guild/default.h"
#include "/std/combat/combat.h"
/*
 * Guild is closed and not returning.
 * New racial was opened in Faerun.
 * 	- Lucius, June 2017
 */
#define H_D_G_H_T "_h_d_g_h_t"
/* by Antharanos */
query_auto_load()
{
    return MASTER;
}
create_object()
{
    set_name("insignia");
    set_adj("black");
    add_adj("adamantine");
    add_name("_h8_insignia");
    set_long("An insignia of black adamantine bearing the distinctive "+
      "runes of House Noquar, the eighth house of the drow city of Undraeth.\n"+
      "Use 'help noquar' to see a list of your commands.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_M_NO_DROP,"You would not dare to drop such a valuable possession!\n");
    add_prop(OBJ_M_NO_SELL,"You would not dare to sell such a valueable possession!\n");
}
public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (for_obj == on)
	data = "You are ";
    else
	data = "From the runic symbols on " + (environment(TO)->query_possessive()) + " forehead, it appears as if " + (environment(TO)->query_pronoun()) + " is ";

    if(on->query_base_stat(SS_RACE) < 5)
	data+="a Servant of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 10)
	data+="a Commoner of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 15)
	data+="an Artisan of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 20)
	data+="a Lesser Warrior of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 25)
	data+="a Warrior of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 30)
	data+="an Elder Warrior of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 40)
	data+="a Lesser Noble of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 50)
	data+="a Noble of House Noquar.\n";
    else
    if(on->query_base_stat(SS_RACE) < 60)
	data+="an Elder Noble of House Noquar.\n";
    else
	data+="a High Noble of House Noquar.\n";

    return data;
}

#if 0

void
enter_env(object to, object from)
{
    remove_name("_h8_insignia");
    if(!to->query_guild_member("Drow race guild"))
    {
	to->catch_msg("Your house insignia dissolves in your hands, as you "+
	  "are no longer a Drow!\n");
	remove_object();
	return;
    }
    add_name("_h8_insignia");
    if(living(environment(TO)))
	to->add_subloc("_h8_insignia",TO);
}

public void
leave_env(object from, object to)
{
    TP->remove_subloc("_h8_insignia");
}
init()
{
    ::init();
    AA(help,help);
    AA(htitles,htitles);
    AA(rem_sub,hthide);
    AA(add_sub,htreveal);
    AA(show_insignia,hshow);
    AA(e_hsmile,hsmile);
    AA(e_hcry,hcry);
    AA(e_hsneer,hsneer);
    AA(e_hpledge,hpledge);
}

#else

public void
init(void)
{
    ::init();
    set_alarm(0.5, 0.0, remove_object);
}

#endif

htitles()
{
    write("A hierarchical list of ranks within House Noquar:\n"+
      "Servant of House Noquar\n"+
      "Commoner of House Noquar\n"+
      "Artisan of House Noquar\n"+
      "Lesser Warrior of House Noquar\n"+
      "Warrior of House Noquar\n"+
      "Elder Warrior of House Noquar\n"+
      "Lesser Noble of House Noquar\n"+
      "Noble of House Noquar\n"+
      "Elder Noble of House Noquar\n"+
      "High Noble of House Noquar\n"+
      "\n");
    return 1;
}
rem_sub()
{
    if(TP->query_prop(H_D_G_H_T))
    {
	write("You are already hiding your house allegiance.\n");
	return 1;
    }
    write("You touch your forehead and whisper a prayer to Lolth, your "+
      "eyes closed tightly.\n"+
      "After a moment, you remove your hand from your forehead.\n"+
      "The runic symbols upon your forehead are now gone!\n");
    write("You now hide your house allegiance.\n");
    say(QCTNAME(TP) + " touches " + TP->query_possessive() + " forehead "+
      "and whispers something with " + TP->query_possessive() + " eyes closed tightly.\n"+
      "After a moment, " + TP->query_pronoun() + " removes " + TP->query_possessive() + " hand "+
      "from " + TP->query_possessive() + " forehead.\n");
    remove_name("_h8_insignia");
    TP->remove_subloc("_h8_insignia");
    TP->add_prop(H_D_G_H_T,1);
    return 1;
}
add_sub()
{
    if(!TP->query_prop(H_D_G_H_T))
    {
	write("You are already showing your house allegiance.\n");
	return 1;
    }
    write("You touch your forehead and whisper a prayer to Lolth, your "+
      "eyes closed tightly.\n"+
      "After a moment, you remove your hand from your forehead.\n"+
      "The runic symbols of House Noquar are now present on your forehead!\n");
    write("You now show your house allegiance.\n");
    say(QCTNAME(TP) + " touches " + TP->query_possessive() + " forehead "+
      "and whispers something with " + TP->query_possessive() + " eyes closed tightly.\n"+
      "After a moment, " + TP->query_pronoun() + " removes " + TP->query_possessive() + " hand "+
      "from " + TP->query_possessive() + " forehead.\n");
    add_name("_h8_insignia");
    TP->add_subloc("_h8_insignia",TO);
    TP->remove_prop(H_D_G_H_T);
    return 1;
}
show_insignia()
{
    write("You proudly show the insignia of House Noquar.\n");
    say(QCTNAME(TP) + " proudly shows the insignia of House Noquar.\n");
    return 1;
}
public int
e_hsmile(string arg)
{
    object *oblist;
    NF("Hsmile at whom?\n");
    if(!strlen(arg))
    {
	allbb(" smiles without fear, for the might of House Noquar is beyond comparison.");
	write("You smile without fear, for the might of House Noquar is beyond comparison.\n");
	SOULDESC("smiling without fear");
	return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
	return 0;
    SOULDESC("smiling without fear");
    actor("You smile at", oblist, " without a trace of fear.");
    all2actbb(" smiles at", oblist, " without a trace of fear.");
    targetbb(" smiles at you without a trace of fear.", oblist);
    return 1;
}
public int
e_hcry(string arg)
{
    object *oblist;
    NF("Hcry at whom?\n");
    if(!strlen(arg))
    {
	allbb(" screams: Noquar ulu usstan! Noquar ultrin!");
	write("You scream: Noquar ulu usstan! Noquar ultrin!\n");
	SOULDESC("screaming a battle-cry");
	return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
	return 0;
    SOULDESC("screaming a battle-cry");
    actor("You turn to", oblist, " and scream: Noquar ultrin!");
    all2actbb(" turns to", oblist, " and screams: Noquar ultrin!");
    targetbb(" turns to you and screams: Noquar ultrin!", oblist);
    return 1;
}
public int
e_hsneer(string arg)
{
    object *oblist;
    NF("Hsneer at whom?\n");
    if(!strlen(arg))
    {
	allbb(" sneers in derision at " + TP->query_possessive() + " surroundings.");
	write("You sneer in derision at your surroundings.\n");
	SOULDESC("sneering in derision");
	return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
	return 0;
    SOULDESC("sneering in derision");
    actor("You sneer in derision at", oblist, ", as though they were a "+
      "slave in the pits of Undraeth.");
    all2actbb(" sneers in derision at", oblist, ", as though they were a "+
      "slave in the pits of Undraeth.");
    targetbb(" sneers in derision at you, as though you were a slave in "+
      "the pits of Undraeth.", oblist);
    return 1;
}
public int
e_hpledge(string arg)
{
    object *oblist;
    NF("Hpledge to whom?\n");
    if(!strlen(arg))
    {
	allbb(" pledges anew " + TP->query_possessive() + " loyalty to Lolth and "+
	  "House Noquar.");
	write("You pledge anew your loyalty to Lolth and House Noquar.\n");
	return 1;
    }
    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if(!sizeof(oblist))
	return 0;
    actor("You pledge your loyalty to", oblist, " in the name of Lolth and House Noquar.");
    all2actbb(" pledges " + TP->query_possessive() + " loyalty to", oblist, " in the "+
      "name of Lolth and House Noquar.");
    targetbb(" pledges " + TP->query_possessive() + " loyalty to you in "+
      "the name of Lolth and House Noquar.", oblist);
    return 1;
}
int
help(string str)
{
    if(!str || str != "noquar")
    {
	NF("Help what? Help noquar?\n");
	return 0;
    }
    write("As a member of House Noquar, the following commands are available to you:\n"+
      "~~~~~~~~~~~~~~~~~~~~~\n"+
      "htitles...A list of house titles.\n"+
      "hthide....Hide your house title.\n"+
      "htreveal..Reveal your house title.\n"+
      "hshow.....Show your house insignia.\n"+
      "hsmile....Smile without a trace of fear.\n"+
      "hcry......Scream out a battle-cry for your house.\n"+
      "hsneer....Sneer in derision at someone(as though they were a slave).\n"+
      "hpledge...Pledge (anew) your loyalty.\n"+
      "~~~~~~~~~~~~~~~~~~~~~\n");
    return 1;
}

public string query_recover() {return 0; }
