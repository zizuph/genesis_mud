/*  
    Gender change shadow, a possible side-effect of Raspatoon the 
    Alchemist's experiment in the Alchemist quest of Gelan.
  

    coder(s):   Maniac

    history:    
              27/8/2000      no linkdeath effect             Maniac
                 4/7/98                 modified             Maniac
                16.1.95                 Created              Maniac
*/

inherit "/std/shadow";
#include <stdproperties.h>
#include <config.h>
#include <macros.h>
#include <const.h>
#include <living_desc.h>
#include "specials.h"
#include ALCHEMIST_QUEST

int new_gender = -1;

/* Matrix of gender transformation strings, first dimension is stage,
   second dimension is from gender, third dimension is to gender */
   
mixed trans_strings = 
  ({
    ({ 
      ({"", 
        "chest becomes feminine.\n", 
        "chest becomes somewhat less masculine.\n" }),
      ({"chest becomes masculine.\n",
        "",
        "chest becomes somewhat less feminine.\n" }),
      ({"chest becomes somewhat more masculine.\n",
        "chest becomes somewhat more feminine.\n",
        ""}) 
     }),
     ({
       ({"",
         "hips widen.\n",
         "hips widen slightly.\n"}),
       ({"hips narrow.\n",
         "",  
         "hips narrow slightly.\n"}),
       ({"hips narrow slightly.\n",
         "hips widen slightly.\n",
         ""}) 
     }),
     ({
       ({"",
         "shoulders narrow markedly.\n",
         "shoulders narrow slightly.\n"}),
       ({"shoulders widen markedly.\n",
         "",  
         "shoulders widen slightly.\n"}),
       ({"shoulders widen slightly.\n",
         "shoulders narrow slightly.\n",
         ""}) 
     }),
     ({
       ({"",
         "nether regions seem to be undergoing a MAJOR change.\n",
         "nether regions seem to be undergoing a minor change.\n"}),
       ({"nether regions seem to be undergoing a MAJOR change.\n",
         "",  
         "nether regions seem to be undergoing a minor change.\n"}),
       ({"nether regions seem to be undergoing a minor change.\n",
         "nether regions seem to be undergoing a minor change.\n",
         ""}) 
     }),
     ({
       ({"",
         "height decreases markedly.\n",
         "height decreases slightly.\n"}),
       ({"height increases markedly.\n",
         "",  
         "height increases slightly.\n"}),
       ({"height increases slightly.\n",
         "height decreases slightly.\n",
         ""}) 
     })
  });


/* Identify player as having gender changed */
int
has_g_change_shadow()
{
    return 1;
}


/* Use instead of remove_object() */
void
destruct_g_change_shadow()
{
  destruct();
}


/* Original gender */
int
query_orig_gender()
{
    return shadow_who->query_gender();
}


/* New gender, the one switched to */
int
query_new_gender()
{
    return new_gender;
}


string
qgs(int g)
{
    return LD_GENDER_MAP[g];
}


void
domain_check()
{
    object env = environment(shadow_who); 

    if ((file_name(env) != OWN_STATUE) &&
        (env->query_domain() != "Calia"))
        remove_shadow(); 
}


void
enter_env(object inv, object from)
{
    shadow_who->enter_env(inv, from); 
    domain_check(); 
}


/* 
   These next few functions shadow all the gender-related functions.
   They are used in preference to set_gender as we don't want to mess
   with saved variables.
 */

/* Return the new gender of the person. */
int
query_gender()
{
    if ((new_gender > -1) && (new_gender <= G_NEUTER))
        return new_gender;
    else
        return shadow_who->query_gender();
}


/* Return the new gender string of the person */
string
query_gender_string()
{
    if ((new_gender > -1) && (new_gender <= G_NEUTER))
        return qgs(new_gender);
    else
        return shadow_who->query_gender_string();
}


/* Return gender-adjusted pronoun */
string
query_pronoun()
{
    if ((new_gender > -1) && (new_gender <= G_NEUTER))
        return LD_PRONOUN_MAP[new_gender];
    else
        return shadow_who->query_pronoun();
}


/* Return gender-adjusted objective */
string
query_objective()
{
    if ((new_gender > -1) && (new_gender <= G_NEUTER))
        return LD_OBJECTIVE_MAP[new_gender];
    else
        return shadow_who->query_objective();
}


/* Return gender-adjusted possessive */
string
query_possessive()
{
    if ((new_gender > -1) && (new_gender <= G_NEUTER))
        return LD_POSSESSIVE_MAP[new_gender];
    else
        return shadow_who->query_possessive();
}


/* carry out the actual transformation */
void
trans(int stage, int old_gen, int new_gen, int transing_back)
{
     switch (stage) {
         case 0:
             tell_room(environment(shadow_who),
                  QCTNAME(shadow_who) + " breaks out in a cold sweat " +
                          "and starts to shiver.\n", shadow_who);
             shadow_who->catch_msg("You break out in a cold sweat " +
                          "and start to shiver.\n");
             set_alarmv(5.0, 0.0, "trans", ({stage+1, old_gen, new_gen,
                             transing_back}) );
             break;
         case 1:
         case 2:
         case 3:
         case 4:
             tell_room(environment(shadow_who),
                  QCTNAME(shadow_who) + "'s " + 
                  trans_strings[stage-1][old_gen][new_gen],
                          shadow_who);
             shadow_who->catch_msg("Your " +
                  trans_strings[stage-1][old_gen][new_gen]);
             set_alarmv(5.0, 0.0, "trans", ({stage+1, old_gen, new_gen,
                                 transing_back}) );
             break;
         case 5:
             tell_room(environment(shadow_who),
                  QCTNAME(shadow_who) + "'s " + 
                  trans_strings[stage-1][old_gen][new_gen] +
                  QCTNAME(shadow_who) + " is now " +  
                  qgs(new_gen) + "!\n",
                          shadow_who);
             shadow_who->catch_msg("Your " +
                  trans_strings[stage-1][old_gen][new_gen] +
                  "You are now " + qgs(new_gen) + "!\n");
             if (transing_back) 
                 destruct_g_change_shadow();
             else 
                 new_gender = new_gen;
             break;
     }
}


/* Initiate transformation from original gender to new gender */
void
trans_to()
{
    int g = shadow_who->query_gender();
    int g_to, *gs;

    gs = ({G_MALE, G_FEMALE, G_NEUTER}) - ({g});
    g_to = gs[random(2)];
    trans(0, g, g_to, 0);
}


/* Initiate transformation back to original gender */
void
trans_back()
{
    int g = shadow_who->query_gender();
    
    if ((new_gender == -1) || (new_gender > G_NEUTER))  
        return;
    trans(0, new_gender, g, 1);
}

