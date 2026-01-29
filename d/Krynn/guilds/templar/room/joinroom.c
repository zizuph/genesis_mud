/**
* Joining room for Templars of Neraka
* Louie  2004
*/

#pragma strict_types

#include "../local.h"

inherit GUILD_IR;

#define TEMPLAR_RULES "_accept_templar_rules"

/** prototypes **/
int join_guild(string str);
int leave_guild(string str);
int accept_rules(string str);
int read_scroll(string str);
string scroll_descrip();
int check_member();

void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    set_short("join room for the Templar Knights");

    set_long("This room is the entrance and sign up area for the "+
        "Templar Knights of Takhisis.  " +
        "Behind a desk sits a Templar Knight, waiting to take "+
        "down the name of anyone who wishes to declare allegiance to the order.  "+
        "A current Templar may also abandon the order here.  "+
        "A scroll on the desk lists the charter of the Templar Knights.  "+
        "The exit is to the south.  "+
        "\n");
    
    add_item(({"desk","knight","templar knight"}),
        "Behind the desk a Templar Knight sits patiently waiting for "+
        "new recruits.  It is possible to <declare allegiance> to "+
        "join the Templar Knights of Takhisis.\n");
        
    add_item(({"charter","scroll"}),
        &scroll_descrip());

    add_exit(ROOM+"hallway1","north",check_member);
    add_exit(ROOM+"road2","south",0);
    add_exit(ROOM+"office","east",check_member);
    
    reset_guild_room();

}

void
init()
{
    ::init();
    add_action(read_scroll, "read");
    add_action(accept_rules, "accept");
    add_action(join_guild, "declare");
    add_action(leave_guild, "abandon");
}

int
check_member()
{
    
    if (TP->query_wiz_level())
    {
        return 0;
    }
    
/*
    if (!(TP->query_guild_name_lay() == GUILD_NAME) &&
*/
    if (!ADMIN->query_member(TP) &&
        !TP->query_pot_member())
    {
        write("Only Templar Knights of Takhisis may enter.\n");
        return 1;
    }
    
    return 0;
}

int
read_scroll(string str)
{
    string descrip;
    
    if (!strlen(str))
    {
        NF("Read what?\n");
        return 0;
    }
    
    if (!(str == "scroll") &&
        !(str =="charter"))
    {
        NF("Read what?\n");
        return 0;
    }
    
    descrip = scroll_descrip();
    
    write(descrip);
    return 1;
}

int
accept_rules(string str)
{
    if (!strlen(str))
    {
        NF("Accept rules?\n");
        return 0;
    }
    
    if (!(str == "rules") && !(str == "the rules"))
    {
        NF("Accept rules?\n");
        return 0;
    }
    
    
    if (TP->query_race_name() == "kender")
    {
        NF("Your kind aren't wanted here!\n");
        return 0;
    }
    
    if (TP->query_guild_name_lay() == GUILD_NAME)
    {
        NF("You're already a Templar Knight!\n");
        return 0;
    }
    
    if (TP->query_prop(TEMPLAR_RULES))
    {
        NF("You've already accepted the rules of the Templar Knights.\n");
        return 0;
    }
    
    write("You accept the rules of the Templar Knights of Takhisis, "+
        "and are now eligible to <declare allegiance> to them.\n");
    TP->add_prop(TEMPLAR_RULES, 1);
    
    return 1;
}

int
join_guild(string str)
{
    object sh;
    string str2;

    if(!strlen(str))
    {
        NF("<Declare allegiance> to the Templar Knights of Takhisis?\n");
        return 0;
    }

    if(!(str == "allegiance") &&
        !(str == "Allegiance") &&
        !(str == "allegiance to the templar knights of takhisis") &&
        !(str == "allegiance to the order")) 
    {
        NF("<Declare allegiance> to the Templar Knights of Takhisis?\n");
        return 0;
    }

    if (TP->query_guild_name_lay() == GUILD_NAME)
    {
        NF("You're already a Templar Knight of Takhisis!\n");
        return 0;
    }
    
    
    if (!TP->query_prop(TEMPLAR_RULES))
    {
        NF("You must have read the scroll and <accept the rules> of "+
            "the Templar Knights first!\n");
        return 0;
    }
    
    /* Clone the shadow */
    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* Does the player qualify for the guild? */
    str2 = sh->player_can_join(TP);
    
    /* a string returned means check failed and str is the reason */
    if (strlen(str2))
    {
        write(str2 + "\n");
        return 1;
    }
    
    /* Attempt to add the shadow. add_lay_shadow() handles messages. */
    
    if (!sh->add_lay_shadow(TP))
    {    
        /* failed to add, so remove shadow */
        sh->remove_shadow();
    } else {
        ADMIN->add_member(TP);
        write("You are handed a black silver-trimmed mantle.\n");
    }
    
    TP->update_hooks();
    return 1;
}

int
leave_guild(string str)
{

    if(!strlen(str))
    {
        NF("Abandon the Templar Knights?\n");
        return 0;
    }

    if(!(str == "the Templars") &&
        !(str == "the templars") &&
        !(str == "templars") &&
        !(str == "Templars") &&
        !(str == "the templar knights") &&
        !(str == "the Templar Knights") &&
        !(str == "templar knights") &&
        !(str == "Templar Knights") &&
        !(str == "the order") &&
        !(str == "order"))
    {
        NF("Abandon the Templar Knights?\n");
        return 0;
    }

    if (!TP->query_guild_member(GUILD_NAME))
    {
        write("You are not a member of the Templar Knights!\n");
        return 1;
    }

    TP->remove_lay_member();
    ADMIN->remove_member(TP);
    write("You leave the Templar Knights of Takhisis.\n");
    
    return 1;
}

string
scroll_descrip()
{
    string desc;
    
    desc =
    "\t"+
    "   ______________________________________________\n\t"+
    " /'\\                                             \\\n\t"+
    "|   |                                             |\n\t"+
    "|  /_____________________________________________/\n\t"+
    "|                                              |\n\t"+ 
    "|                                              |\n\t"+
    "|  The Templar Knights of Takhisis are the     |\n\t"+
    "|  protectors of Queen Takhisis' interests     |\n\t"+
    "|  and desires.                                |\n\t"+
    "|                                              |\n\t"+
    "|  Those who serve as Knights of Her Temple    |\n\t"+
    "|  are the guardians of Her territories and    |\n\t"+
    "|  servants.                                   |\n\t"+
    "|                                              |\n\t"+
    "|  The Templar Knights do not limit their      |\n\t"+
    "|  membership - however, within the Templar    |\n\t"+
    "|  Knights are those who have been selected    |\n\t"+
    "|  by Her Priesthood for their loyalty and     |\n\t"+
    "|  proven service to the Dark Queen.  Beware   |\n\t"+
    "|  whom you may offend with your actions!      |\n\t"+
    "|                                              |\n\t"+
    "|  Those who wish to serve Her Dark Majesty    |\n\t"+
    "|  in worship and combat are well cautioned to |\n\t"+
    "|  keep in mind these guidelines:              |\n\t"+
    "|                                              |\n\t"+
    "|  - The Templar Knights are a layman fighter  |\n\t"+
    "|      guild.                                  |\n\t"+
    "|                                              |\n\t"+
    "|  - Those who serve Her are expected to have  |\n\t"+
    "|      hearts black enough for Her duties,     |\n\t"+
    "|      those who do not will be removed.       |\n\t"+
    "|                                              |\n\t"+
    "|  - The Priesthood of Takhisis are favored    |\n\t"+
    "|      in Her eyes and should be respected,    |\n\t"+
    "|      and protected, as such.                 |\n\t"+
    "|                                              |\n\t"+
    "|  Those who join the Knights of Her Temple    |\n\t"+
    "|  will receive special training in:           |\n\t"+
    "|                                              |\n\t"+
    "|   club               superior journeyman     |\n\t"+
    "|   unarmed            superior journeyman     |\n\t"+
    "|   defence            superior journeyman     |\n\t"+
    "|   parry              superior journeyman     |\n\t"+
    "|   blindfighting      superior journeyman     |\n\t"+
    "|   appraise enemy     superior craftsman      |\n\t"+
    "|   tracking           confident journeyman    |\n\t"+
    "|   awareness          superior craftsman      |\n\t"+
    "|                                              |\n\t"+
    "|  Along with these skills are abilities       |\n\t"+
    "|  that enable Templars Knights to avoid       |\n\t"+
    "|  and deal damage in combat.                  |\n\t"+
    "|                                              |\n\t"+
    "|                                              |\n\t"+
    "|  Those who decide to abandon the Temple, or  |\n\t"+
    "|  those who are chased out, may face the loss |\n\t"+
    "|  of knowledge gained in these walls as well  |\n\t"+
    "|  a weakening in their body as appropriate.   |\n\t"+
    "|                                              |\n\t"+
    "|  Those who wish to declare their allegiance  |\n\t"+
    "|  to the Templar Knights must first agree to  |\n\t"+
    "|  these rules by <accept rules>.              |\n\t"+
    "|                                              |\n\t"+
    "|     _________________________________________|__\n\t"+
    " \\__/____________________________________________/\n";
    
    
    return desc;
}
