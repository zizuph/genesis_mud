#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/d/Kalad/std/monster";


object gMaster;

void
create_monster()
{
    set_name("baalzebub");
    set_adj("fiendish");
    add_adj("shadow");
    add_name("demon");
    set_short("fiendish shadow demon of the Netherworld");

    set_long("You are looking at what appears to be a creature "+
    "made out of the blackest black. No features are visible, save "+
    "for two red glowing orbs in what appears to be a head. The whole "+
    "shape looks like a gargoyle of some sort, with large black wings "+
    "that flap around. This creature looks like something right out of "+
    "a nightmare.\n");

    set_stats(({1,1,1,1,1,1}));

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_SEE_DARK,5);

    add_prop(OBJ_M_NO_ATTACK,"It doesn't seem to be on this "+
    "plane of existance, and so you cannot attack it.\n");
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    tell_room(E(ob),"The "+short()+" fades away!\n");
    remove_object();
}

void
set_master(object ob)
{
    tell_object(ob,"You are in control of the "+short()+" for now.\n");
    tell_object(ob,"You can do 'demon help' for commands.\n");
    gMaster = ob;
}

int
do_help(string str)
{
    if(TP != gMaster)
        return 0;
    if(str != "help")
        return 0;
    write("You can do these commands:\n"+
    "dspeak          -   Make the demon say something.\n"+
    "dwail           -   Make the demon wail.\n"+
    "dchuckle        -   Make the demon chuckle.\n"+
    "dlaugh          -   Make the demon laugh.\n"+
    "dbrood          -   Make the demon brood.\n"+
    "dgaze [target]  -   Make the demon gaze at someone.\n"+
    "descape         -   Make the demon try to escape, but fail.\n"+
    "dreturn         -   Make the demon return back to where it came.\n"+
    "dglare [target] -   Make the demon glare at someone.\n");
    return 1;
}

int
do_speak(string str)
{
    if(TP != gMaster)
        return 0;
    NF("Dspeak what?\n");
    if(!str)
        return 0;
    tell_room(E(TO),"The "+short()+" roars: "+str+"\n");
    return 1;
}

int
do_wail(string str)
{
    if(TP != gMaster)
        return 0;
    tell_room(E(TO),"The "+short()+" screetches a demonic wail that "+
    "leaves your ears ringing!\n");
    return 1;
}

int
do_escape(string str)
{
    if(TP != gMaster)
        return 0;
    tell_room(E(TO),"The "+short()+" suddenly tries to jump out at "+
    "you, but slams into an invisible shield that surrounds it.\n");
    return 1;
}

int
do_chuckle()
{
    if(TP != gMaster)
        return 0;
    tell_room(E(TO),"The "+short()+" chuckles in a deep, sinister "+
    "manner; its blazing orbs flashing with unholy amusement.\n");
    return 1;
}

int
do_laugh()
{
    if(TP != gMaster)
        return 0;
    tell_room(E(TO),"The "+short()+" roars a horrible, demonic "+
    "laugh!\n");
    return 1;
}

int
do_return()
{
    if(TP != gMaster)
        return 0;
    tell_room(E(TO),"The "+short()+" suddenly sinks back into the "+
    "ground.\n");
    remove_object();
    return 1;
}

int
do_brood()
{
    if(TP != gMaster)
        return 0;
    tell_room(E(TO),"The "+short()+" shuts its eyes and looks "+
    "thoughtful for a moment.\n");
    return 1;
}


void
init_living()
{
    ::init_living();
    add_action(do_speak,"dspeak");
    add_action(do_wail,"dwail");
    add_action(do_help,"demon");
    add_action(do_escape,"descape");
    add_action(do_chuckle,"dchuckle");
    add_action(do_laugh,"dlaugh");
    add_action(do_brood,"dbrood");
    add_action(do_return,"dreturn");
}

