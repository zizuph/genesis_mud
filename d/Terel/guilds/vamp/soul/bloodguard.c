
#include "../guild.h"

inherit "/lib/commands";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

int
accept(string str)
{
    notify_fail("Accept which bloodguard?\n");
    if (!strlen(str))
    {
        return 0;
    }
    if (!CAN_SEE_IN_ROOM(TP))
    {
        return 0;
    }
    object * oblist=parse_live(str,"[the] %l");
    
    if (sizeof(oblist)!=1)
    {
        return 0;
    }

    if (!IS_BG(oblist[0]))
    {
        return 0;
    }

    if (oblist[0]->query_master()==TP->query_real_name())
    {
        TP->catch_msg(QCTNAME(oblist[0]) + " is already your "+
        "Bloodguard.\n");
        return 1;
    }
    
    actor("You place your hands on the sides of", oblist, "'s head "+
    "and focus your mind, aligning " + POSS(oblist[0]) + " thoughts with "+
    "your own. " + capitalize(PRO(oblist[0])) + " is now yours.");
    
    all2actbb(" places " + POSS(TP) + " hands on",oblist,"'s head for "+
    "a moment.");
    
    target(" places " + POSS(TP) + " hands on the sides of your head, " +
    "looking deeply into your eyes. You feel a bond between your minds "+
    "grow - " + PRO(TP) + " is your master now.",oblist);
    LAY_MANAGER->set_master(oblist[0],TP);
    return 1;
}

int 
reject(string str)
{
    notify_fail("Reject which bloodguard?\n");
    if (!strlen(str))
    {
        return 0;
    }
    if (!CAN_SEE_IN_ROOM(TP))
    {
        return 0;
    }
    object * oblist=parse_live(str,"[the] %l");
    
    if (sizeof(oblist)!=1)
    {
        return 0;
    }

    if (!IS_BG(oblist[0]))
    {
        return 0;
    }

    if (oblist[0]->query_master()!=TP->query_real_name())
    {
        TP->catch_msg(QCTNAME(oblist[0]) + " is not your Bloodguard.\n");
        return 1;
    }

    actor("You break your mental connection with", oblist, ", leaving "+
    OBJ(oblist[0])+" without your connection to the gift.");
    
    all2actbb(" looks away from",oblist," in disdain.");
    
    target(" severs the mental connection with you, leaving your "+
    "connection to the gift more distant and fuzzy.",oblist);
    
    LAY_MANAGER->remove_master(oblist[0]);
    return 1;
}


int 
offer(string str)
{
    notify_fail("Offer your blood to whom?\n");
    if (!strlen(str))
    {
        return 0;
    }
    if (!CAN_SEE_IN_ROOM(TP))
    {
        return 0;
    }
    object * oblist=parse_live(str,"[the] %l");
    
    if (sizeof(oblist)!=1)
    {
        return 0;
    }

    if (!IS_VAMP(oblist[0]))
    {
        return 0;
    }
    
    TP->add_prop(LIVE_O_OFFERED_BLOOD,oblist[0]);
    
    actor("You offer",oblist," a taste of your blood.");
    
    target(" offers you a taste of "+POSS(TP)+" blood.",oblist);
    
    all2act(" offers",oblist," a taste of "+POSS(TP)+" blood.");
    
    oblist->hook_offered_blood(TP);
    
    return 1;
    
}

