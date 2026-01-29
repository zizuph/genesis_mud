// file name: dblarm.c
// creator(s): denis
// revision history:
// purpose: used by dblpole.c as special defence object.
// note:
// bug(s):
// to-do:

inherit "/std/armour.c";
#include "/d/Avenir/common/common.h"

int id;                        // Removing alarm id

object pole_object;            // Double-bladed polearm object

create_armour()
{
    set_name("_Avenir_dblarm");

    set_at(A_MAGIC);
    set_ac(20);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_M_NO_DROP,1);

    set_af(TO);
    set_no_show();
}

/*-----[ What does it protect? ]-----*/
public int *
query_shield_slots()
{
    return(({A_BODY,A_HEAD,A_LEGS,A_L_ARM,A_R_ARM}));
}

mixed wear()
{
    write("You start to spin the double-bladed polearm before yourself, "+
          "creating unpenetratable shield.\n");
    tell_room(environment(TP),QCTNAME(TP)+" starts to spin "+POSSESS(TP)+
          " double-bladed polearm before "+OBJECTIVE(TP)+"self, creating "+
          "unpenetratable shield.\n",TP); 
    id=set_alarm(itof(random(60)+10),0.0,"stop_defence");
    return 1;
}

mixed remove()
{
    write("You stop to spin double-bladed polearm before yourself.\n");
    tell_room(environment(TP),QCTNAME(TP)+ " stops to spin "+POSSESS(TP)+
          " double-bladed polearm around "+OBJECTIVE(TP)+"self.\n",TP);
    return 1;
}

stop_defence()
{
    remove_me();
    pole_object->reset_defence();
    remove_object();
}

set_pole(object pole)
{
    pole_object=pole;
}

varargs int
got_hit(int hid, int ph, object enemy, int dt, int dam)
{
    string how;

    if(ph<20&&random(2))
    {
        mixed res;
        res=enemy->hit_me(15,W_SLASH,query_worn(),-1);
        switch(res[2])
        {
        case 0..9:
            how=", making little damage.\n";
            break;
        case 10..39:
            how=", leaving several injures behind.\n";
            break;
        default:
            how=", tearing into bits.\n";
            break;
        }

        query_worn()->catch_msg(
          "Your spinning polearm repels attack of "+QTNAME(enemy)+how);
        enemy->catch_msg(
          "Your attack at "+QTNAME(query_worn())+" is repelled by "+
	  POSSESS(query_worn())+" spinning polearm"+how);
        pole_object->tell_watcher(
          "The attack of "+QTNAME(enemy)+" at "+QTNAME(query_worn())+
	  " is repelled "+
          "by "+POSSESS(query_worn())+" spining polearm"+how,enemy);
    }
    return ::got_hit(hid,ph,enemy,dt,dam);
}
