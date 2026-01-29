inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
#define MIN_TEAR_BOUND 500
#define SUCK_TIME 10.0
#define MIN_SUCK_BOUND 100
 
object tp;
 
void create_object()
 {
    set_short("knife, sucking blood from your wound");
    set_long("This magical knife was thrown at you by the "+
             "evil mage and now it is sucking your blood!\n");
    set_name("_sucking_knife_");
    add_name("knife");
    add_prop(OBJ_M_NO_DROP,"You cannot drop it, you can only try to "+
             "tear it, but it will probably hurt you.\n");
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,100);
 }
 
void init()
 {
    ::init();
    add_action("do_tear","tear");
 }
 
int do_tear(string par)
 {
    int dam;
    int bound;
 
    bound=TP->query_max_hp()*20/100;
    if (bound<MIN_TEAR_BOUND) bound=MIN_TEAR_BOUND;
    dam=random(bound);
    write("You tear knife out from your body, but it hurts you.\n"+
          "Magical knife disappears.\n");
    say(QCTNAME(TP)+" tears knife out from "+HIS_HER(TP)+" body, "+
        "but it seems very hurt for "+HIM_HER(TP)+".\n");
    TP->heal_hp(-dam);
    if (TP->query_hp()==0)
     {
        write("Wave of blood flowns from your body!\n");
        say("Wave of blood flowns from "+QTNAME(TP)+" body!\n");
        TP->do_die(TO);
     }
    remove_object();
    return 1;
 }
 
void do_suck()
 {
    int bound,dam;
 
    if (tp->query_ghost())
     {
        tp->catch_msg("Since you're already dead, the knife disappears.\n");
        remove_object();
        return;
     }
    if (tp)
     {
        bound=tp->query_max_hp()*3/100;
        if (bound<MIN_SUCK_BOUND) bound=MIN_SUCK_BOUND;
        dam=random(bound);
        tp->catch_msg("Your lifeforces are sucked away by the "+
                      "magical knife.\n");
        tell_room(ENV(tp),QCTNAME(tp)+"'s lifeforces are sucked "+
                  "away by the magical knife.\n",tp);
        tp->heal_hp(-dam);
        if (tp->query_hp()==0)
         {
            tp->catch_msg("You're totally drained by the knife!\n"+
                          "You fall to the floor.\n");
            tell_room(ENV(tp),QCTNAME(tp)+" is totally drained by the "+
                      "knife, "+HE_SHE(tp)+" falls to the floor.\n",tp);
            tp->do_die(TO);
         }
     }
 }
 
void init_suck(object who)
 {
    tp=who;
    tp->catch_msg("As magical knife impales your body you scream "+
                  "in pain:\n");
    tell_room(ENV(tp),"Magical knife impales "+QTNAME(tp)+"'s "+
              "body.\n",tp);
    tp->command("scream");
    set_alarm(SUCK_TIME,SUCK_TIME,"do_suck");
    set_alarm(60.0,0.0,"destruct_knife");
 }
 
void destruct_knife()
 {
    tp->catch_msg("Suddenly knife sucking your lifeforce disappears!\n");
    tell_room(ENV(tp),"Suddenly knife sucking "+QTNAME(tp)+"'s "+
              "lifeforces disappears.\n",tp);
    remove_object();
 }
