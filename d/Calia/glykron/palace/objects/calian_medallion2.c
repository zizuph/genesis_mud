
/* 
    This is the guild object of the Calian guild in the crystalline palace. 
    It adds the cmdsoul to mortal Calians from init(); 
    It provides the guild's member to member tell, i.e. "project to". 
    It also changes material gradually when one makes net contributions 
    to the rack of the guild. 

    coder(s):   Glykron & Maniac 
    history: 
      added "image", the emote equivalent to "project", Maniac, 14/12/00
      turns to broken glass for players who take a massive amount 
          more than they give to the rack, Maniac, 24/9/2000
      turns to glass for players who take a lot 
         more than they give to rack, Maniac, 19/5/2000 
      changed to wearable item, Maniac, 29/11/98
      changed skill to tint conversion, Maniac, 1/3/97 
      added setup_plain_desc() and setup_rack_desc(), Maniac, 13/11/96
      Added rack-related tint feature, Maniac, 11/11/96
      changed handling of project spell, 31/10/96
      bug sorted out, Maniac, 2/9/96
      messages changed, Maniac, 13/8/96 
      Project made into proper spell, Maniac, 15/7/96
      "list project to" feature added, Maniac, 17/6/96
      Made into armour instead of object, Maniac, 30/5/96
*/

#pragma save_binary

inherit "/std/object"; 
inherit "/lib/wearable_item"; 
inherit "/d/Genesis/cmd/double"; 
#include <stdproperties.h>
#include <options.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <language.h>
#include <flags.h>
#include <wa_types.h>
#include "defs.h"
#include CALIAN_HEADER
#include "/d/Genesis/cmd/emotes.h" 

int project_alarm, ready_to_project; 
int image_alarm, ready_to_image; 
string receiver_name, project_message, project_message2; 
object project_receiver; 

int project_to(string str); 
int image_to(string str); 

static string *med_tints = MEDALLION_TINTS; 


int
is_calian(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}


/*
 * Function name: lpr
 * Description:   lists the last few received Calian projects,
 *                by calling a function in the Calian shadow. 
 * Returns:       success
 */
int 
do_lpr()
{
    object tp = this_player(); 

    if (!is_calian(tp))
        return 0;

    tp->list_project_to();
    return 1;
}


/*
 * Function:     do_project
 * Description:  the alarm to "project" executes this function
 */ 
void
do_project(object tp, string str)
{
    if (!objectp(tp))
        return;

    if (project_alarm) 
        project_alarm = 0; 
    ready_to_project = 1; 

    tp->command("project to " + str); 
}


/* 
 * Function:     do_image
 * Description:  the alarm to "image" executes this function 
 */ 
void
do_image(object tp, string str)
{
    if (!objectp(tp)) 
        return; 

    if (image_alarm) 
        image_alarm = 0; 
    ready_to_image = 1; 

    tp->command("image " + str); 
}


/*
 * Function name: project_to_player
 * Description:   executes the project to player command, used 
 *                in "project to all" 
 * Arguments:     str - predicate
 * Returns:       success
 */
int
project_to_player(object player, string message)
{
    if (!is_calian(player) || player->query_wiz_level())
        return 0; 

    ready_to_project = 1; 
    return project_to("to " + player->query_real_name() + " " + message); 
}


/* 
 * Function name: image_to_player
 * Description:   executes the image to player command, used 
 *                in "image to all"
 * Arguments:     str - predicate
 * Returns:       success
 */
int
image_to_player(object player, string message)
{
    if (!is_calian(player) || player->query_wiz_level())
        return 0; 

    ready_to_image = 1; 
    return image_to("to " + player->query_real_name() + " " + message);
}


private void
reset_spell_ready_vars()
{
    ready_to_project = ready_to_image = 0; 
}


private void
reset_spell_prep_vars()
{
    receiver_name = project_message = project_message2 = 0; 
    project_receiver = 0; 
}


/* 
 * Function name: project_to 
 * Description:   executes the project to command 
 * Arguments:     str - predicate 
 * Returns:       success 
 */
int
project_to(string str)
{
    string prep; 
    object tp, medallion; 
    int wizard; 
    mixed tmp; 

    tp = TP; 
    wizard = tp->query_wiz_level(); 

    if (project_alarm)  { 
        NF("You are preparing the project spell.\n"); 
        reset_spell_ready_vars(); 
        return 0; 
    } 
    else if (image_alarm) { 
        NF("You are preparing the image spell.\n"); 
        reset_spell_ready_vars(); 
        return 0; 
    } 

    if (!objectp(project_receiver) || !stringp(project_message)) { 
        if (!stringp(str) || explode(str, " ")[0] != "to")  { 
            NF("Project to whom ?\n"); 
            reset_spell_ready_vars(); 
            return 0; 
        } 

        if (sscanf(str, "%s %s", prep, str) != 2) { 
            NF("Project to whom ?\n"); 
            reset_spell_ready_vars(); 
            return 0;
        }

        if (sscanf(str, "%s %s", receiver_name, project_message) != 2) {
            NF("Project what ?\n");
            reset_spell_ready_vars();
            return 0;
        }

        if (!is_calian(tp)) {
            NF("Nothing happens.\n");
            reset_spell_ready_vars();
            return 0; /* project to cannot be used by non-members */
        }

        if (query_worn() != tp) {
            NF("You must wear your medallion in order to project or receive.\n");
            reset_spell_ready_vars(); 
            return 0; 
        }

        tmp = environment(tp)->query_prop(ROOM_M_NO_MAGIC); 
        if (stringp(tmp)) { 
            NF(tmp); 
            reset_spell_ready_vars(); 
            return 0; 
        } 
        else if (intp(tmp) && tmp)  { 
            NF("Magic is not possible in this room.\n"); 
            reset_spell_ready_vars(); 
            return 0; 
        } 

        if ((receiver_name == "all") && wizard) { 
            map(users(), &project_to_player(,str)); 
            reset_spell_ready_vars(); 
            return 1; 
        } 
        project_receiver = find_living(receiver_name); 
    } 

    if (tp->query_mana() < 10) { 
        write("You don't feel mentally strong enough to communicate " + 
              "the message.\n"); 
        reset_spell_ready_vars(); 
        return 1; 
    } 

    if (!wizard && !project_alarm && !ready_to_project) { 
        tp->add_mana(-10); 
        tell_object(tp, "You concentrate on your " + short() + ".\n"); 
        tell_room(environment(tp), QCTNAME(tp) + " concentrates.\n", tp); 
        project_alarm = 
              set_alarm(itof(PROJECT_PREP_TIME), 0.0, &do_project(tp, str)); 
        return 1; 
    } 

    reset_spell_ready_vars(); 

    if (!objectp(project_receiver) || (project_receiver == tp) || 
        !objectp(medallion = present(MEDALLION_ID, project_receiver)) || 
        project_receiver->query_linkdead() || 
       (project_receiver->query_wiz_level() && 
        project_receiver->query_invis())) { 
        write("Your message is not received.\n"); 
        reset_spell_prep_vars(); 
        return 1; 
    } 

    if ((medallion->query_worn() != project_receiver) || 
        (project_receiver->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M)) { 
        write(capitalize(receiver_name) + "'s mind is distant, " + 
              "perhaps " + project_receiver->query_pronoun() + 
              " is busy with something.\n"); 
        reset_spell_prep_vars(); 
        return 1; 
    } 

    if (!is_calian(project_receiver)) { 
        write("The mind of that person " + 
              "is not receptive to your thoughts.\n");
        reset_spell_prep_vars(); 
        return 1;
    }

    /* treat project to as a spell with small fail chance */
    if (!wizard && tp->resolve_task(TASK_SIMPLE + 50, ({ TS_INT }) ) < 1)
    {
       write("Your concentration lapses and your attempted project " + 
             "spell fails.\n"); 
       reset_spell_prep_vars(); 
       return 1;
    } 

    project_receiver->catch_project_to(tp->query_real_name(), 
                      project_message); 
    if (tp->query_option(OPT_ECHO)) 
        tell_object(tp, "You project a thought to " + 
                        capitalize(receiver_name) + 
                        ":\n" + capitalize(project_message) + "\n"); 
    else 
        tell_object(tp, "Ok.\n"); 

    if (project_receiver->query_mana() < 20) 
        tell_object(tp, "You feel a great tiredness in the mind of " + 
                        "the receiver.\n"); 
    reset_spell_prep_vars(); 
    return 1; 
}


/* 
 * Function:     query_emote_text 
 * Description:  returns an emote string of the form: 
 *               "<actor> <verb>ing [target] [adverb]" 
 * Arguments:    edet - emote semantic details (same format as 
 *                      in the 'double' emote soul) 
 *               rcvr - the receiver of the emote description 
 *               ing  - whether the emote verb(s) should be in 
 *                      "ing" form 
 * Returns:      the text of the emote 
 * 
 */ 
string 
query_emote_text(mixed edet, object rcvr, int ing) 
{
    int i, apf, tpf, s; 
    object trg, act; 
    string msg, ad; 
    mixed sen, elr; 

    /* unpacking the array makes the code below more readable */ 
    act = edet[EVH_VDI_ACT]; 
    trg = edet[EVH_VDI_TRG]; 
    sen = edet[EVH_VDI_SEN]; 
    ad = edet[EVH_VDI_ADV]; 

    msg = ""; 

    s = sizeof(sen); 

    /* 
     * Construct the message by resolving all the sentence elements, 
     * keeping a running count of actor and target references. 
     */ 
    i = 0; 
    while (i < s) { 
        elr = resolve_sen_el(rcvr, act, trg, sen[i], 
                             ad, 0, ing, apf, tpf); 
        msg += elr[0]; 
        apf += elr[1]; 
        tpf += elr[2]; 
        i++; 
    } 

    return msg; 
}


/* 
 * Function name: image 
 * Description:   executes the image command 
 * Arguments:     str - predicate 
 * Returns:       success 
 */
int
image_to(string str)
{
    string ev, str2; 
    object tp, medallion; 
    int i, wizard; 
    mixed tmp; 

    tp = TP; 
    wizard = tp->query_wiz_level(); 

    if (image_alarm)  { 
        NF("You are preparing the image spell.\n"); 
        reset_spell_ready_vars(); 
        return 0; 
    } 

    if (project_alarm)  { 
        NF("You are preparing the project spell.\n"); 
        reset_spell_ready_vars(); 
        return 0; 
    } 

    if (!stringp(project_message) || !objectp(project_message2) || 
        !objectp(project_receiver)) { 
        if (!stringp(str) || 
            (sscanf(str, "%s %s", receiver_name, str2) != 2)) { 
            NF("Image <person> <emotion>?\n"); 
            reset_spell_ready_vars(); 
            return 0; 
        } 

        if (sscanf(str2, "%s %s", ev, str2) != 2) { 
            ev = str2; 
            str2 = 0; 
        } 

        if (!is_calian(tp)) { 
            NF("Nothing happens.\n"); 
            reset_spell_ready_vars(); 
            return 0; /* project to cannot be used by non-members */ 
        } 

        if (query_worn() != tp) { 
            NF("You must wear your medallion in order to image or receive.\n"); 
            reset_spell_ready_vars(); 
            return 0; 
        } 

        tmp = environment(tp)->query_prop(ROOM_M_NO_MAGIC); 
        if (stringp(tmp)) { 
            NF(tmp); 
            reset_spell_ready_vars(); 
            return 0; 
        } 
        else if (intp(tmp) && tmp)  { 
            NF("Magic is not possible in this room.\n"); 
            reset_spell_ready_vars(); 
            return 0; 
        } 

        if ((receiver_name == "all") && wizard) { 
            map(users(), &image_to_player(,str)); 
            reset_spell_ready_vars(); 
            return 1; 
        } 

        if (objectp(project_receiver = find_living(receiver_name))) { 

            /* Check to see whether the target of the emote is 
               someone who is not in the room */ 
            if (stringp(str2)) { 
                if (lower_case(str2) && str2 == receiver_name) { 
                    str2 = project_receiver->query_objective(); 
                } 
                if (sizeof(tmp = explode(str2, " ")) > 1) { 
                    for (i = 0; i < sizeof(tmp); i++) { 
                        if (lower_case(tmp[i]) == receiver_name) 
                            tmp[i] = "it"; 
                    } 
                    str2 = implode(tmp, " "); 
                } 
            } 

            if (!pointerp(tmp = get_emote_details(ev, str2, project_receiver))) 
                return 0; 

            project_message = query_emote_text(tmp, tp, 1); 
            project_message2 = query_emote_text(tmp, project_receiver, 1); 

        } 
    } 

    if (tp->query_mana() < 10) { 
        write("You don't feel mentally strong enough to communicate " + 
              "the message.\n"); 
        reset_spell_ready_vars(); 
        return 1; 
    } 

    if (!wizard && !image_alarm && !ready_to_image) { 
        tp->add_mana(-10); 
        tell_object(tp, "You concentrate on your " + short() + ".\n"); 
        tell_room(environment(tp), QCTNAME(tp) + " concentrates.\n", tp); 
        image_alarm = 
              set_alarm(itof(PROJECT_PREP_TIME), 0.0, &do_image(tp, str)); 
        return 1; 
    } 

    reset_spell_ready_vars(); 

    if (!objectp(project_receiver) || (project_receiver == tp) || 
        !objectp(medallion = present(MEDALLION_ID, project_receiver)) || 
        project_receiver->query_linkdead() || 
        (project_receiver->query_wiz_level() && 
         project_receiver->query_invis())) { 
        write("Your image is not received.\n"); 
        reset_spell_prep_vars(); 
        return 1; 
    } 

    if ((medallion->query_worn() != project_receiver) || 
         (project_receiver->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M)) { 
        write(capitalize(receiver_name) + "'s mind is distant, " + 
              "perhaps " + project_receiver->query_pronoun() + " is busy " + 
              "with something.\n"); 
        reset_spell_prep_vars(); 
        return 1; 
    } 

    if (!is_calian(project_receiver)) { 
        write("The mind of that person " + 
              "is not receptive to your thoughts.\n"); 
        reset_spell_prep_vars(); 
        return 1; 
    } 

    /* treat project to as a spell with small fail chance */
    if (!wizard && tp->resolve_task(TASK_SIMPLE + 50, ({ TS_INT }) ) < 1)
    {
       write("Your concentration lapses and your attempted image " + 
             "spell fails.\n"); 
       reset_spell_prep_vars(); 
       return 1; 
    } 

    project_receiver->catch_projected_image(tp->query_real_name(), 
        "An image of" + project_message2 + " appears in your mind.\n"); 
    if (tp->query_option(OPT_ECHO)) 
        tell_object(tp, "An image of" + project_message + 
                        " appears in " + capitalize(receiver_name) + 
                        "'s mind.\n"); 
    else 
        tell_object(tp, "Ok.\n"); 

    if (project_receiver->query_mana() < 20) 
        tell_object(tp, "You feel a great tiredness in the mind of " + 
                        "the receiver.\n"); 
    reset_spell_prep_vars(); 
    return 1; 
}


/* 
 * Add a command soul to the player, activate its commands. 
 */
void
check_soul(object tp)
{
    string *soul_list;

    seteuid(getuid());
    soul_list = tp->query_cmdsoul_list();

    if (member_array(SPECIAL("calian_cmdsoul"), soul_list) == -1)
    {
        tp->add_cmdsoul(SPECIAL("calian_cmdsoul"));
        tp->update_hooks();
    }
}


string
query_recover()
{
    return 0;
}


string 
query_auto_load() 
{ 
    return MASTER; 
} 


void 
do_med_wear() 
{ 
    object e = environment(this_object()); 
    seteuid(getuid()); 
    if (living(e) && !objectp(query_worn())) { 
        clone_object("/d/Calia/palace/objects/calian_medallion")->move(e); 
        remove_object(); 
    } 
} 


string 
long_func()
{
    return 
       ( "It is " + LANG_ADDART(short()) + ", " + 
         "bearing an insignia of someone thinking very hard. " + 
        (is_calian(TP) ? 
           ("You notice the commands \"project to\", " + 
            "\"image\", \"lpr\" and \"help calian\" engraved on it.  ") : 
            "" ) + 
        "\n"); 
}


void
create_object()
{
    set_name( ({ "medallion" }) ); 
    set_adj( ({ "crystalline", "calian", "Calian" }) ); 
    set_short("crystalline medallion"); 
    set_pshort("crystalline medallions"); 
    set_long("@@long_func"); 
    config_wearable_item(A_NECK, 1, 6, this_object()); 
    add_prop(OBJ_I_VALUE, 0); 
    add_prop(OBJ_I_WEIGHT, 1); 
    add_prop(OBJ_I_VOLUME, 1); 
    add_prop(OBJ_M_NO_STEAL, 1); 
    set_alarm(2.0, 0.0, do_med_wear); 
}


void
crumble_check()
{
    object e = environment(this_object());
    if (living(e) && (e->query_alignment() < MEDALLION_MIN_ALIGN)) {
        e->catch_msg("Your " + short() + " crumbles to dust.\n");
        remove_object();
    }
}


void 
setup_rack_desc(object tp)
{
   int sz, sk, st, lv; 
   string tint;

   if (!(sz = sizeof(med_tints))) 
       return; 

   sk = tp->query_skill(CALIAN_RACK_POINTS); 
   if (sk < -100000) {
       log_file("rack_takers", tp->query_real_name() + " " + sk + "\n"); 
       remove_adj(query_adj(1)); 
       set_adj(({"glass", "calian", "Calian"})); 
       if (sk < -250000) { 
           add_adj("broken"); 
           set_short("broken glass medallion"); 
           set_pshort("broken glass medallions");
       } 
       else {
           set_short("glass medallion"); 
           set_pshort("glass medallions"); 
       } 
       return; 
   } 

   if (sk < 0)
       return;

   st = ftoi(pow(itof(sk), 1.0 / 3.0));   

   lv = ((sz * st) / 100); 
   if (lv >= sz) 
       lv = sz - 1;

   tint = med_tints[lv]; 

   remove_adj(query_adj(1)); 
   set_adj(({"crystalline", "calian", "Calian"}) + explode(tint, " ")); 
   set_short("crystalline medallion with " + LANG_ADDART(tint) + " tint"); 
   set_pshort("crystalline medallions with " + LANG_ADDART(tint) + " tint"); 
}


void
setup_plain_desc(object tp)
{
   int sk; 

   if ((sk = tp->query_skill(CALIAN_RACK_POINTS)) < -100000) { 
       log_file("rack_takers", tp->query_real_name() + " " + sk + "\n"); 
       remove_adj(query_adj(1)); 
       set_adj(({"glass", "calian", "Calian"})); 
       if (sk < -250000) { 
           add_adj("broken"); 
           set_short("broken glass medallion"); 
           set_pshort("broken glass medallions"); 
       } 
       else {
           set_short("glass medallion"); 
           set_pshort("glass medallions");
       } 
       return; 
   } 
   remove_adj(query_adj(1)); 
   set_adj(({"crystalline", "calian", "Calian"})); 
   set_short("crystalline medallion"); 
   set_pshort("crystalline medallions"); 
}


void
update_tint(object tp)
{
   if (!objectp(tp)) 
       return; 

   if (tp->query_skill(CALIAN_OPTIONS) & CALOPT_RACK_CLUB) 
       setup_rack_desc(tp); 
   else 
       setup_plain_desc(tp); 
}


/* Person shouldn't be able to carry more than one of these around */ 
void
enter_env(object dest, object old)
{
    object *obs;
    int i, change;

    set_alarm(1.0, 0.0, crumble_check);
    obs = all_inventory(dest);

    change = 0;
    for (i = 0; i < sizeof(obs); i++)
    {
	if (obs[i]->id(MEDALLION_ID) && obs[i] != this_object())
	{
	    obs[i]->remove_object();
	    change++;
	}
    }

    if (change)
	  environment()->catch_msg("The medallions melt together!\n");
    ::enter_env(dest, old);

    if (interactive(dest) && is_calian(dest)) 
        set_alarm(1.0, 0.0, &update_tint(dest)); 
}


void
leave_env(object from, object to)
{
    ::leave_env(from, to); 
    wearable_item_leave_env(from, to); 
}


void
init()
{
    object tp; 

    ::init(); 
    add_action(project_to, "project"); 
    add_action(do_lpr, "lpr"); 
    add_action(image_to, "image"); 

    if (is_calian(tp = TP))
        set_alarm(1.0, 0.0, &check_soul(tp));
}
