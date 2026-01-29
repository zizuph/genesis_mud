
/* 
   Code to be inherited into statue-creatures on Mount Kyrus,
   Statues may guard the mountain at various points to stop enemies or 
   perhaps also people of evil alignment from getting past, by transforming 
   into creatures and attacking.

   Features: 
    -  support for transforming from being inanimate to animate and 
                 vise versa. 
    -  now all code is resident in the one creature, the inanimate 
                 and animate parts used to be separate. 
    -  crumble to dust when they die.  

   The creation function is: 
       create_creature_statue()

   Configuring functions are: 
      set_animate_short(anl) 
      set_animate_long(string anl) 
      set_inanimate_short(string ins), 
      set_inanimate_long(string inl) 
      set_min_avg_stat_to_attack(int min_avg) 
      set_max_avg_stat_to_attack(int max_avg) 
      set_disallow_evil_align(int max_al)
      set_direc_blocks(string *directions)
      enable_give_warning()
      disable_give_warning()

   coded Maniac 16.6.95
   recoded by Maniac 7/2/97
   revised, Maniac, 17/5/97
*/


#pragma save_binary

#include "/d/Calia/domain.h"
#include CALIAN_GUILD_BASE_DEF
#include COUNCIL_HEADER
#include <macros.h>
#include <stdproperties.h>

inherit "/std/creature"; 

#define ANIMATE 1
#define INANIMATE 2

void set_statue_state(int new_state); 

string *enemies = ({ });
string *direc_blocks = ({ }); 
string *warned = ({ });
string animate_long; 
string inanimate_long; 
string animate_short; 
string inanimate_short; 
int statue_state = 0;
int give_warning = 0;
int max_avg_stat_to_attack = 0;
int min_avg_stat_to_attack = 0;
int disallow_evil_align = 0;

int check_alarm = 0;


void
enable_give_warning()
{
    give_warning = 1; 
}

void
disable_give_warning()
{
    give_warning = 0; 
}

void
set_animate_short(string s)
{
     if (!stringp(s)) 
         return;
     animate_short = s; 
}

void
make_animate_short()
{
    if (stringp(animate_short)) 
       this_object()->set_short(animate_short); 
}

void
set_animate_long(string s)
{
    if (!stringp(s)) 
        return;
    animate_long = s; 
}

void
make_animate_long()
{
     if (stringp(animate_long))
         this_object()->set_long(animate_long); 
}

void
set_inanimate_short(string s)
{
     if (!stringp(s)) 
         return;
     inanimate_short = s; 
}

void
make_inanimate_short()
{
    if (stringp(inanimate_short)) 
       this_object()->set_short(inanimate_short); 
}

void
set_inanimate_long(string s)
{
    if (!stringp(s)) 
        return;
    inanimate_long = s; 
}

void
make_inanimate_long()
{
     if (stringp(inanimate_long)) 
         this_object()->set_long(inanimate_long); 
}

private void
enemy_check()
{
    object *en, *left_en;
    int i, j;

    left_en = ({ });
    en = this_object()->query_enemy(-1);
    for (i = 0; i < sizeof(en); i++)
        if (objectp(en[i]))
           if (present(en[i], environment(this_object())))   
               left_en += ({en[i]});
           else {
               this_object()->stop_fight(en[i]);
               en[i]->stop_fight(this_object());
           }

    if (!sizeof(left_en)) {
        set_statue_state(INANIMATE);          
        return;
    }
    check_alarm = set_alarm(300.0, 0.0, enemy_check);     
}

void
set_statue_state(int new_state)
{
    if (new_state == INANIMATE) { 
        if (statue_state == INANIMATE || objectp(query_attack())) 
            return;
        else {  
            if (objectp(environment(this_object()))) 
                command("emote becomes inanimate.");  
            statue_state = INANIMATE;  
            make_inanimate_short(); 
            make_inanimate_long(); 
            if (check_alarm) {
                remove_alarm(check_alarm); 
                check_alarm = 0; 
            }   
            return;
        } 
    } 
    if (new_state == ANIMATE) { 
        if (statue_state == ANIMATE)
            return;
        else { 
            if (objectp(environment(this_object()))) 
                command("emote animates!"); 
            statue_state = ANIMATE;  
            make_animate_short(); 
            make_animate_long(); 
            if (!check_alarm)
                check_alarm = set_alarm(100.0, 0.0, enemy_check); 
            return;
        } 
    } 
}

void
create_creature_statue()
{
}

mixed
statue_no_attack()
{
    if (statue_state == INANIMATE) 
        return "Kill what?\n";
     return 0;
}

mixed
statue_no_give()
{
    if (statue_state == INANIMATE) 
        return 1;
    return "isn't interested in gifts.\n";
}

nomask void
create_creature()
{
    seteuid(getuid()); 
    set_race_name("statue"); 
    add_prop(NPC_I_NO_FEAR, 1); 
    add_prop(OBJ_I_RES_POISON, 100); 
    add_prop(OBJ_I_RES_FIRE, 100); 
    add_prop(NPC_M_NO_ACCEPT_GIVE, statue_no_give); 
    add_prop(OBJ_M_NO_ATTACK, statue_no_attack);  
    add_prop(OBJ_M_NO_MAGIC_ATTACK, statue_no_attack);  
    create_creature_statue(); 
    set_statue_state(INANIMATE); 
}

void
attack_object(object ob)
{
    set_statue_state(ANIMATE);  
    ::attack_object(ob); 
}

void
attacked_by(object ob)
{
    set_statue_state(ANIMATE);  
    ::attacked_by(ob); 
}



/* Set what level evil alignments begin to be disallowed, if any */
void
set_disallow_evil_align(int i)
{
    if (i >= 0)
        disallow_evil_align = 0;
    else
        disallow_evil_align = i;
}


/* Set the maximum average stat necessary for the player to be attacked */
void
set_max_avg_stat_to_attack(int i)
{
    if (i < 1)
        i = 0;

    max_avg_stat_to_attack = i;
}

/* Set the minimum average stat necessary for the player to be attacked */
void
set_min_avg_stat_to_attack(int i)
{
    if (i < 1)
        i = 0;

    min_avg_stat_to_attack = i;
}


void
enter_env(object dest, object old)
{
    int i;
    mixed ex;

    ::enter_env(dest, old); 

    if (sizeof(ex = dest->query_exit())) { 
        for (i = 0; i < sizeof(ex); i+= 3) {  
            if (member_array(ex[i+1], direc_blocks) > -1) {  
                dest->remove_exit(ex[i+1]); 
                dest->add_exit(ex[i], ex[i+1], 
                      VBFC_ME("cannot_pass_creature"), 1); 
            } 
       } 
   } 
}


/* 
 * For creatures, given a player who is trying to pass  
 * return 1 if he's not allowed to pass, 0 if he is. 
 */
int
cannot_pass_creature() 
{
    int al, avg, en, nm, wn;
    object tp = this_player(); 

    if (!objectp(tp) || !interactive(tp))
        return 0;

    avg = tp->query_average_stat();
    if (max_avg_stat_to_attack)
        if (avg > max_avg_stat_to_attack)
            return 0;

    if (min_avg_stat_to_attack)
        if (avg < min_avg_stat_to_attack)
            return 0;

    al = tp->query_alignment();

    wn = member_array(tp->query_real_name(), warned) + 1;
    nm = tp->query_real_name(); 
    en = COUNCIL_CODE->is_enemy(nm); 

    if (statue_state == INANIMATE) { 
    if (en || ((disallow_evil_align < 0) && (al <= disallow_evil_align))) {
        tell_object(tp, "You try to pass the statue.\n");
        tell_room(environment(tp), 
               QCTNAME(tp) + " tries to pass the statue.\n", tp);
        if ((wn && give_warning) || !give_warning) {
            command("kill " + nm);
            return 1;
        }
        else  {
            if (!wn)
                warned += ({ tp->query_real_name() });
            tp->catch_msg("With a sound of grating stone, " +
                this_object()->query_the_name(tp) + 
                " cranes its neck around to face you, glaring ominously. " +
                "You take a step back.\n");
            tell_room(environment(tp), "With a sound of grating stone, " +
                QTNAME(this_object()) + " cranes its neck around " +
                "to face " + QTNAME(tp) + ", glaring ominously.\n", tp);
            return 1;
        }
    }
    } 

    if (en || ((disallow_evil_align < 0) && (al <= disallow_evil_align))) {
        tell_object(tp, "You try to pass the statue.\n" + 
                    this_object()->query_The_name(tp) + " blocks you.\n");
        tell_room(environment(tp), QCTNAME(tp) + " tries to pass the " +
                  "statue.\n"+ QCTNAME(this_object()) + " blocks " +  
                  tp->query_objective() + ".\n", tp);
        if (!objectp(query_attack())) 
            command("kill " + nm); 
        return 1;
    }
   return 0;
}


void
set_direc_blocks(string *db)
{
    if (pointerp(db)) 
        direc_blocks = db; 
}


varargs string 
show_sublocs(object for_obj, mixed *slocs)
{
    if (statue_state == INANIMATE)  
         return ""; 
    else
         return ::show_sublocs(for_obj, slocs); 
}

