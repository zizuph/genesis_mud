/*
 * Explorer Club Emotes
 * 
 * Tomas -- Dec. 1999
 * 
 */

#pragma save_binary

#include <wa_types.h>
#include <composite.h>
#include <cmdparse.h>

#define SOULDESC(x)     (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define PRO(x)   (x->query_pronoun())

/* Some filter functions */
private int male (object ob) { return ob->query_gender() == G_MALE; }
private int female (object ob) { return ob->query_gender() == G_FEMALE; }


/*
 *     ereel
 */
int
e_reel(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You reel in delight as you uncover " +
       "another mystery of the arcane.\n");
    allbb(" reels in delight as "+ PRO(TP) +" uncovers " +
       "another mystery of the arcane.\n");
    return 1;
}


/*
 *     esmile 
 */
int
e_smile(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You smile revealing wisdom of ages past.\n");
    allbb(" smiles revealing wisdom of ages past.\n");
    return 1;
}


/*
 *     estare 
 */
int
e_stare(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You stare distantly as you attempt to recall something " +
       "learned in the past.\n");
    allbb(" stares distantly as if trying to remember something.\n");
    return 1;
}

public int
other_members(object ob)
{
    if (IS_MEMBER(ob) && present(EXPLORER_RING, ob) && ob != TP)
        return 1;
    return 0;
}



public int
e_who(string str)
{
    object *mm;
    int i;
    mm = filter(users(), other_members);

    if (!sizeof(mm)) {
        TP->catch_msg("You do not sense the presence of " +
                      "other Explorers.\n");
        return 1;
    }
    TP->catch_msg("You sense the presence of:\n");
    for (i=0; i<sizeof(mm); i++)
         TP->catch_msg(capitalize(mm[i]->query_real_name()) + " " +
                   mm[i]->query_title() + "\n");
    return 1;
}



/*
 slook <target> -- Looks at <target> with the wisdom of the ancients.

 srespect <historian_member> -- Looks to you with respect and
                                 admiration.
  soffer -- Offers to show you the wisdom of the ancients.

  swonder <target> -- Wonders how <target> can breathe let alone
                      think for themselves.
*/


