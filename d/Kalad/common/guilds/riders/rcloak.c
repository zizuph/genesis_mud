inherit "/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    set_name("cloak");
    add_adj("flowing");
    set_adj("blood-red");
    set_short("flowing blood-red cloak");
    set_long("This cloak is made of a fine blood-red material, "+
    "it is not too heavy so you don't get too hot in the sun. "+
    "There is a silver sigil of the Riders on the back: A huge "+
    "Warwolf snarling with a sword in it's mouth. Try <rtoss>, "+
    "<rstand> and <rshow> for some cloakish emotes.\n");
    set_at(A_ROBE);
    set_ac(5);
    add_prop(OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,600);
    add_prop(OBJ_I_VALUE,140);
}

void
init()
{
     ::init();
     add_action("do_rshow","rshow");
     add_action("do_rtoss","rtoss");
     add_action("do_rstand","rstand");
}

int do_rstand()
{
	if(TP->query_guild_name_lay() != "Riders of the Dark Alliance")
    {
        write("Nice cloak huh, too bad you aren't a Rider of the Dark "+
        "Alliance, you might actually look cool if you were.\n");
        say(QCTNAME(TP)+" tries to look cool in "+HIS(TP)+" flowing "+
        "blood-red cloak, but fails.\n");
        TP->command("blush");
        return 1; 
    }
    say(QCTNAME(TP)+" smirks as "+HE(TP)+" squares "+HIS(TP)+" shoulders, stands up straight, and folds "+
    HIS(TP)+" arms across "+HIS(TP)+" chest. The blood-red cloak flows in the "+
    "breeze majestically.\n");
    write("You stand up straight with your arms folded across your chest, your cloak blows in "+
    "the breeze as you wear a smirk on your face.\n");
    return 1;
}

int do_rshow()
{
	if(TP->query_guild_name_lay() != "Riders of the Dark Alliance")
    {
        write("Nice cloak huh, too bad you aren't a Rider of the "+
        "Dark Alliance, you might actually look cool, if you were.\n");
        say(QCTNAME(TP)+" tries to look cool in "+HIS(TP)+" flowing "+
        "blood-red cloak, but fails.\n");
        TP->command("blush");
        return 1; 
    }
    say(QCTNAME(TP)+" turns "+HIS(TP)+" back to you, proudly displaying the "+
    "silver sigil of the Dark Alliance on the back of "+HIS(TP)+" flowing "+
    "blood-red cloak.\n");
    write("You proudly display the sigil of the Dark Alliance to everyone.\n");
    return 1;
}

int do_rtoss()
{
	if(TP->query_guild_name_lay() != "Riders of the Dark Alliance")
    {
        write("Nice cloak huh, too bad you aren't a Rider of the "+
        "Dark Alliance, you might actually look cool, if you were.\n");
        say(QCTNAME(TP)+" tries to look cool in "+HIS(TP)+" flowing "+
        "blood-red cloak, but fails.\n");
        TP->command("blush");
        return 1; 
    }
    say(QCTNAME(TP)+" tosses his flowing blood-red cloak back over his shoulder, in "+
    "preparation for the battle to come.\n");
    write("You toss your cloak back over your shoulder in preparation for the battle to "+
    "come.\n");
    return 1;
}