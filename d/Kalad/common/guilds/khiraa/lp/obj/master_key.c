inherit "/std/key.c";
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"

#define MAX_LEVEL 26

/* The Master key of the Khiraa */
/* Sarr 4.Sep.97 */

int sealed;

void
create_key()
{
    set_name("skull-key");
    add_name("key");
    add_name("_kmaster_key_");
    set_key("_khiraa_master_key_");
    set_adj(({"skull","obsidian"}));
    set_short("obsidian skull-key");
    set_long("This key is shaped like a small human skull. The eyes "+
    "of the skull hold glowing red rubies. A magic, ancient and strong, "+
    "radiates from this artifact. You see 'help kkey'\n");
    add_prop(OBJ_I_VOLUME,5);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_DROP,1);
    sealed = 0;
    seteuid(getuid());
}

int
do_help(string str)
{
    if(str != "kkey")
        return 0;
    write("With this key, you have these powers: \n"+
    "cpromote <person> <lvl>  : Promote someone a certain amount\n"+
    "cdemote <person> <lvl>   : Demote someone a certain amount\n"+
    "ccheck <person>          : Check someone's current level\n"+
    "ccircle <person>         : Add someone to the circle\n"+
    "                         : If already a member of the circle, remove\n"+
    "                         : If no argument, list members\n"+
    "cgrant <person>          : Grant someone permission to join the guild\n"+
    "cfriend                  : List the friends of the Khiraa\n"+
    "cfriend <person>         : Declare this one as a friend of the Khiraa\n"+
    "                         : If already a friend, will remove from list\n"+
    "cseeker                  : List the seekers of the Khiraa\n"+
    "cseeker <person> for <?> : Make this one an offical seeker of the \n"+
    "                         : Khiraa. Doing it to someone already one \n"+
    "                         : will remove them. Fill in the '<?>' with\n"+
    "                         : either 'knighthood' or 'priesthood'.\n"+
    "cexpel <person>          : Expel this fool from the Khiraa\n"+
    "cdisgrace <person>       : Put the Disgrace penalty on someone\n"+
    "cseal                    : seal/unseal the temple\n");
    return 1;
}

int
do_seeker(string str)
{
    int i;
    string *names,s1,s2;
    mapping temp;
    object ob;

    if(!str)
    {
        write(KHIRAA_SERVER->list_seekers());
        return 1;
    }

    sscanf(str,"%s for %s",s1,s2);
    if(!s2)
        s1 = str;

    if(KHIRAA_SERVER->remove_seeker(s1,TP->query_name()) )
    {
        write("You have removed "+C(s1)+" as a seeker of the Khiraa.\n");
        return 1;
    }

    NF("You must do: cseeker <name> for <knighthood/priesthood>\n");
    if(s2 != "knighthood" && s2 != "priesthood")
        return 0;

    write("You have declared "+C(s1)+" as a seeker of the "+s2+" of the "+
    "Khiraa.\n");

    KHIRAA_SERVER->add_seeker(s1,s2,TP->query_name());

    return 1;
}
    
int
do_friend(string str)
{
    if(!str)
    {
        write(KHIRAA_SERVER->list_friends());
        return 1;
    }

    if(KHIRAA_SERVER->remove_friend(str,TP->query_name()) )
    {
        write("You have removed "+C(str)+" as a friend of the Khiraa.\n");
        return 1;
    }

    write("You have declared "+C(str)+" as a friend of the Khiraa.\n");

    KHIRAA_SERVER->add_friend(str,TP->query_name());
    return 1;
}

int
do_disgrace(string str)
{
    mapping temp;
    object ob;

    NF("That one is not of the Khiraa.\n");
    if(!str)
        return 0;
    if(!KHIRAA_SERVER->member_exists(str))
        return 0;
    ob = find_player(str);        
    if(objectp(ob))
    {
        tell_object(ob,"You have been punished with the disgraced "+
        "order by "+TP->query_name()+" for actions against the Horror's will.\n");
    }
    KHIRAA_SERVER->set_guild_order(ob->query_real_name(),-1);
    write("You have punished "+C(str)+" with the disgraced order.\n");

    return 1;
}

int
do_check(string str)
{
    int lvl;
    NF("That one is not of the Khiraa.\n");

    if(!str)
        return 0;

    if(!KHIRAA_SERVER->member_exists(str))
        return 0;

    lvl = KHIRAA_SERVER->query_guild_order(str);

    write(C(str)+" is at the level: "+lvl+".\n");
    return 1;
}

int
do_demote(string str)
{
    string name;
    int lvl,old_lvl;
    object me;

    NF("Demote who how many levels?\n");
    if(sscanf(str,"%s %d",name,lvl) != 2)
        return 0;
    if(!KHIRAA_SERVER->member_exists(name))
        return 0;
    NF("You cannot demote that one any further.\n");
    old_lvl = KHIRAA_SERVER->query_guild_order(name);
    if((old_lvl - lvl) < 1)
        return 0;

    KHIRAA_SERVER->set_guild_order(name, (old_lvl - lvl) );

    write("You have demoted "+C(name)+" "+lvl+" "+ 
    (lvl > 1 ? "levels.\n" : "level.\n"));

    me = find_player(name);
    if(objectp(me))
        tell_object(me,"You have been demoted "+lvl+" "+
        (lvl > 1 ? "levels.\n" : "level.\n"));

    return 1;
}

int
do_promote(string str)
{
    string name;
    int lvl,old_lvl;
    object me;

    NF("Promote who how many levels?\n");
    if(sscanf(str,"%s %d",name,lvl) != 2)
        return 0;
    if(!KHIRAA_SERVER->member_exists(name))
        return 0;
    NF("You cannot promote that one any further.\n");
    old_lvl = KHIRAA_SERVER->query_guild_order(name);
    if((old_lvl + lvl) > MAX_LEVEL)
        return 0;

    KHIRAA_SERVER->set_guild_order(name, (old_lvl + lvl) );

    write("You have promoted "+C(name)+" "+lvl+" "+ 
    ( lvl > 1 ? "levels.\n" : "level.\n"));

    me = find_player(name);
    if(objectp(me))
        tell_object(me,"You have been promoted "+lvl+" "+
        (lvl > 1 ? "levels" : "level")+" by "+TP->query_name()+".\n");
    return 1;
}

int
do_seal()
{
    if(sealed == 0)
    {
        (KHIRAA+"temple/rooms/circle_private")->do_seal("temple entrance");
        sealed = 1;
        return 1;
    }
    else
    {
        (KHIRAA+"temple/rooms/circle_private")->do_unseal("temple entrance");
        sealed = 0;
        return 1;    
    }
}

int
do_circle(string str)
{
    object me;
    string list;
    NF("Circle who?\n");
    if(!str)
    {
        list = KHIRAA_SERVER->query_circle_members();
        write(list);
        return 1;
    }
    NF("Only the Circle Leader may add/remove to the Circle.\n");
    if(TP->query_circle() != 2)
        return 0;

    NF("You cannot remove yourself from the circle in this manner.\n");
    if(TP->query_real_name() == str)
        return 0;
    NF(C(str)+" is not a member of the Khiraa.\n");
    if(!KHIRAA_SERVER->member_exists(str))
        return 0;
    me = find_player(str);
    if(KHIRAA_SERVER->query_circle_member(str))
    { 
        KHIRAA_SERVER->add_circle_member(str,0);
        write("You remove "+C(str)+" from the Circle of the Khiraa.\n");
        if(objectp(me))
            tell_object(me,"You have been removed from the Circle.\n");
    }
    else
    {
        KHIRAA_SERVER->add_circle_member(str,1);
        write("You have added "+C(str)+" as a new member of the Circle.\n");
        if(objectp(me))
            tell_object(me,"You have been added as a new member of the Circle.\n");
    }
    return 1;
}


int
do_grant(string str)
{
    object me;
    NF("Grant permission to join to whom?\n");
    if(!str)
        return 0;
    me = find_player(str);
    NF("That person is not logged in.\n");
    if(!objectp(me))
        return 0;

    tell_object(me,"\n-<( You have been granted permission to join "+
    "the Khiraa by "+TP->query_name()+" )>-\n");
    write("You have granted "+me->query_name()+" permission to "+
    "join the Khiraa.\n");
    me->add_prop(KHIRAA_CIRCLE_PERMISSION,1);
    return 1;
}

int
do_expel(string name)
{
    return 1;
}

void
init()
{
    ::init();
    add_action(do_help,"help");
    add_action(do_seal,"cseal");    
    add_action(do_promote,"cpromote");
    add_action(do_demote,"cdemote");
    add_action(do_check,"ccheck");
    add_action(do_disgrace,"cdisgrace");
    add_action(do_friend,"cfriend");
    add_action(do_seeker,"cseeker");
    add_action(do_circle,"ccircle");
    add_action(do_grant,"cgrant");
    add_action(do_expel,"cexpel");
}

void
melt_it()
{
    tell_object(E(TO),"The "+short()+" slowly fades from view.\n");
    set_this_player(E(TO));
    say(QCTNAME(TP)+
    " gasps in horror as the "+short()+" he has melts away.\n");
    remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    if(living(to))
    {
        if(!IS_DK(to) && !IS_LP(to))
        set_alarm(0.5,0.0,&melt_it());
    }
}

