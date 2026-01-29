#pragma strict_types
/*
 * /d/Avenir/registry/relate.c
 * creator(s): Gwyneth, Dec 2003
 * updates:    Lilith, 2  Mar 2004 - adding checks for purchased seal.
 *             Lilith, 27 Feb 2004 - added COMPOSITE_WORDS to sign to
 *                     reduce maintenace when relate.h is updated. 
 *             Lilith, 24 Feb 2004 - room description
 *             Lucius, May 2015: Code refactoring and cleanups
 *             Lucius, Dec 2017: Code re-write and bug fixes.
 *
 * This room keeps track of relationships. A player may register,
 * unregister or list relationships and claims. A player may also request
 * proof of the registration, which will get him/her a piece of paper
 * outlining his/her claims and relationships.
 * When a person makes a claim, it first checks to see if a matching
 * claim has been made. If so, it moves both claims to a relationship,
 * since they both agree. (I know, you don't have to have the other
 * person to agree to be an enemy, but that will just have to wait for
 * the next version, if any.) If there is no matching claim, then the
 * relationship is added as a claim. This allows players to make
 * relationships with non-existant players. For example:
 * Jane claims to be the descendant of Manwe.
 * Whenever a claim or relationship is added or removed, it checks
 * if the player has proof and updates it to avoid a call to the
 * room each time the paper is looked at. No emotes or shadow at this
 * point.
 *
 * Known problems: There might be a little bit of stickiness when
 * trying to add a relationship with the same person in the same
 * category (such as being life-bound and pair-bound at the same time).
 *
 * Cynrede = old english for kindred
 */
inherit "/std/room";

#include <files.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#include "relate.h"

#define NF	notify_fail
#define TP	this_player()

/* Ex: ([ "jane" : ([ "parent" : ([ "mother" : ({ "jim", "john" }) ]),
                      "child"  : ([ "daughter" : ({ "jean", "al" }) ]),
                      "enemy"  : ([ "enemy" : ({ "sally" }),
                                    "mortal-enemy" : ({ "amanda" }) ]) ]) ])
*/


public mapping gClaims = ([]),
               gRelates = ([]);

public static mapping m_relates = RELATES, matching = MATCHING;
public static string *cats = sort_array(m_indices(m_relates));


public int proof(string str);


/*
 * Function name: read_sign
 * Description  : Returns text on how to register a relationship.
 */
public string
read_sign(void)
{
    return "Cynredes that can be registered are as follows:\n"+
      " 1. Ancestor/Descendant: ancestor and ancestress - descendant and heir\n" +
      " 2. Grandparent/Grandchild: "+ COMPOSITE_WORDS(GRANDPARENT) +"\n" +
      "        - "+ COMPOSITE_WORDS(GRANDCHILD) +"\n" +
      " 3. Spouse: "+ COMPOSITE_WORDS(SPOUSE) +"\n" +
      " 4. Patron/Concubine: "+ COMPOSITE_WORDS(PATRON)+"\n" +
      "        - "+ COMPOSITE_WORDS(CONCUBINE)+"\n" +
      " 5. Sibling-Spouse: "+ COMPOSITE_WORDS(SIBSPOUSE) +"\n" +
      " 6. Parent/Child: "+ COMPOSITE_WORDS(PARENT) +"\n"+
      "        - "+ COMPOSITE_WORDS(CHILD) +"\n"+
      " 7. Step-Parent/Step-Child: "+ COMPOSITE_WORDS(STEPPARENT) +"\n" +
      "        - "+ COMPOSITE_WORDS(STEPCHILD)+"\n" +
      " 8. Sibling: "+ COMPOSITE_WORDS(SIBLING) +"\n" +
      " 9. Cousin: "+ COMPOSITE_WORDS(COUSIN) +"\n"+
      "10. Uncle-Aunt/Nephew-Niece: uncle and aunt - nephew and niece\n" +
      "11. Foster: "+ COMPOSITE_WORDS(FOSTER) +"\n" +
      "12. Friend: "+ COMPOSITE_WORDS(FRIEND) +"\n" +
      "13. Lover: "+ COMPOSITE_WORDS(LOVER) +"\n" +
      "14. Fiance/Fiancee: "+ COMPOSITE_WORDS(FIANCE) +"\n" +
      "15. Master/Servant: "+ COMPOSITE_WORDS(MASTR) +"\n"+
      "        - "+ COMPOSITE_WORDS(SERVANT) +"\n"+
      "16. Bound: "+ COMPOSITE_WORDS(BOUND) +"\n" +
      "17. Warder/Ward: "+ COMPOSITE_WORDS(WARDER) +"\n"+
      "        - "+ COMPOSITE_WORDS(WARD) +"\n"+
      "18. Enemy: "+ COMPOSITE_WORDS(ENEMY) +"\n"+
      "19. Relative: "+ COMPOSITE_WORDS(RELATIVE) +"\n"+
      "20. Ex: ex\n\n"+
      "You must purchase a seal before you can register.\n"+
      "Examine the instructions for syntax information on "+
      "registering and unregistering relationships.\n";
}

/*
 * Function name: instructions
 * Description  : Returns text on general instructions
 */
public string
instructions(void)
{
    return "You must purchase a seal before you can register.\n"+
        "To register a relationship:\n"+
        "   > 'register <category> [relationship] <name>'\n" +
        "For example, to claim to be the son of Jane, you would enter:\n" +
        "   > 'register child son jane' or 'register child jane'\n" +
        "     and then enter 'son' when prompted.\n"+
	"To register as Jane's mother:\n" +
        "   > 'register parent mother jane' or 'register parent jane'\n\n" +
        "To unregister a relationship or claim:\n" +
        "   > 'unregister <category> <relationship> <name>'\n"+
	"For example: 'unregister lover girlfriend jane'.\n\n"+
        "Claims become confirmed relationships when a corresponding "+
        "claim is made.\n"+
        "You may 'list claims' that have been made of you.\n"+
        "You may also list another's claims and relationships by "+
        "'list <name>', or you may list everyone who has made a claim "+
        "or relationship with 'list names'.\n\n"+
        "If you've registered here, you may 'request " +
        "proof' of your claims and relationships.\n\n"+
        "Examine the sign for more details on the types of relationships "+
        "that can be registered.\n\n";
}

public void
create_room(void)
{
    set_short("registrar of relationships");
    set_long("This is the Bazaar office of the Registry of Cynrede. "+
        "It is here that relationships between people are claimed "+
        "and formally recognized. "+
        "This long rectangular room is actually part of the larger "+
        "square building, separated into two rooms by a long counter. "+
        "Beyond the counter can be seen countless rows of shelves "+
        "and towering stacks of vellum. "+
        "You can examine the large sign hanging from the ceiling "+
        "and the instructions that have been posted at intervals "+
        "down the counter.\n");

    add_exit("/d/Avenir/common/bazaar/admin/a3", "south", 0);

    add_item(({"vellum", "stacks" }),
        "Stacks of vellum for tracking the registrations are filed "+
        "in the shelves in an attempt to keep everything organized.\n");
    add_item(({"wood", "dark wood"}), 
        "A beautiful, glossy wood with a narrow even grain.\n");
    add_item(({"shelves", "rows"}), 
        "The shelves are made of the same dark, glossy wood as the "+
        "counter. They are lined up in rows, filling the entire "+
        "room.\n");
    add_item(({"counter", "long counter"}), 
        "It is a long counter made of a dark, glossy wood. It divides "+
        "a very large room into halves, one side for the public, the "+
        "other for storing voluminous amounts of vellum.\n");
    add_item(({"sign", "large sign"}), read_sign);
    add_item(({"poster", "instructions"}), instructions);
    add_cmd_item(({"sign", "large sign"}), "read", read_sign);
    add_cmd_item(({"poster", "instructions"}), "read", instructions);

    IN_IN;
    add_prop(ROOM_M_NO_ATTACK, 1);

    add_npc(REGISTRY + "registrar");

    restore_object(MASTER);
}

/*
 * Function name: update_proof
 * Description  : Updates the paper held by the player after a change
 *                in registration.
 * Arguments    : string who, string name - the players needing an update.
 */
public varargs void
update_proof(string who, string with)
{
    object player;

    // For find_player() to work, name must be lower case.
    if (strlen(who = lower_case(who)))
    {
        // For present() to work, there must be a player.
        if (objectp(player = find_player(who)))
            present(PROOF_ID, player)->update_list();
    }

    if (strlen(with = lower_case(with)))
    {
        if (objectp(player = find_player(with)))
            present(PROOF_ID, player)->update_list();
    }
}

/*
 * Function name: query_relates
 * Description  : Returns an array of every name that has a relationship
 *                associated with it.
 */
public string *
query_relates(void)	{ return m_indices(gRelates); }

/*
 * Function name: query_claims
 * Description  : Returns an array of every name that has made a claim.
 */
public string *
query_claims(void)	{ return m_indices(gClaims); }

/*
 * Function name: query_relate_cats
 * Description  : Returns an array of all of the categories that 'who'
 *                has relationships in.
 * Arguments    : string who - the player we want to know categories for
 */
public string *
query_relate_cats(string who)
{
    mixed data = gRelates[capitalize(who)];

    if (m_sizeof(data))
	return m_indices(data);
    else
	return ({ });
}

/*
 * Function name: query_claim_cats
 * Description  : Returns an array of all of the categories that 'who'
 *                has made claims in.
 * Arguments    : string who - the player we want to know categories for
 */
public string *
query_claim_cats(string who)
{
    mixed data = gClaims[capitalize(who)];

    if (m_sizeof(data))
	return m_indices(data);
    else
	return ({ });
}

/*
 * Function name: query_relate_relates
 * Description  : Returns an array of all of the relationships in
 *                category 'cat' for the player 'who'.
 * Arguments    : string who - the player with the relationships
 *                string cat - the category to check
 * Returns      : Ex. query_relate_relates("jane", "friend") might
 *                return ({ "friend", "girlfriend" }).
 */
public string *
query_relate_relates(string who, string cat)
{
    who = capitalize(who);
    cat = lower_case(cat);

    if (member_array(cat, query_relate_cats(who)) == -1)
        return ({ });

    return m_indices(gRelates[who][cat]);
}

/*
 * Function name: query_claim_relates
 * Description  : Returns an array of all of the made claims in
 *                category 'cat' for the player 'who'.
 * Arguments    : string who - the player with the claims
 *                string cat - the category to check
 * Returns      : Ex. query_claim_relates("jane", "friend") might
 *                return ({ "friend", "girlfriend" }).
 */
public string *
query_claim_relates(string who, string cat)
{
    who = capitalize(who);
    cat = lower_case(cat);

    if (member_array(cat, query_claim_cats(who)) == -1)
        return ({ });

    return m_indices(gClaims[who][cat]);
}

/*
 * Function name: query_relate_names
 * Description  : Returns an array of names that have the relationship
 *                'relate' in the category 'cat' to the player 'who'.
 * Arguments    : string who - the player with the relationship
 *                string cat - the category to check
 *                string relate - the relationship within cat to check
 * Returns      : Ex. query_relate_names("jane", "friend", "friend") might
 *                return ({ "joe", "jim", "jill" })
 */
public string *
query_relate_names(string who, string cat, string relate)
{
    who = capitalize(who);
    cat = lower_case(cat);
    relate = lower_case(relate);

    if (member_array(relate, query_relate_relates(who, cat)) == -1)
        return ({ });

    return gRelates[who][cat][relate];
}

/*
 * Function name: query_claim_names
 * Description  : Returns an array of names that have the claim
 *                'relate' in the category 'cat' to the player 'who'.
 * Arguments    : string who - the player with the claim
 *                string cat - the category to check
 *                string relate - the relationship within cat to check
 * Returns      : Ex. query_claim_names("jane", "friend", "friend") might
 *                return ({ "joe", "jim", "jill" })
 */
public string *
query_claim_names(string who, string cat, string relate)
{
    who = capitalize(who);
    cat = lower_case(cat);
    relate = lower_case(relate);

    if (member_array(relate, query_claim_relates(who, cat)) == -1)
        return ({ });

    return gClaims[who][cat][relate];
}

/*
 * Function name: query_claim_map
 * Description  : Returns the mapping associated with gClaims[who]
 * Arguments    : string who - the name to check for
 * Returns      : See description
 */
public mapping
query_claim_map(string who)
{
    return (gClaims[capitalize(who)] ?: ([]));
}

/*
 * Function name: query_relate_map
 * Description  : Returns the mapping associated with gRelates[who]
 * Arguments    : string who - the name to check for
 * Returns      : See description
 */
public mapping
query_relate_map(string who)
{
    return (gRelates[capitalize(who)] ?: ([]));
}

/*
 * Function name: add_claim
 * Description  : Add a new claim to gClaims.
 * Arguments    : string who - the person who claims the relationship
 *                string with - the person 'who' claims the relationship with
 *                string cat - the category of the relationship
 *                string relate - the specific relationship
 */
public void
add_claim(string who, string with, string cat, string relate)
{
    mixed data = gClaims[capitalize(who)];
    relate = lower_case(relate);
    with = capitalize(with);
    cat = lower_case(cat);

    if (!m_sizeof(data))
        gClaims[who] = ([ cat : ([ relate : ({ with }) ]) ]);
    else if (!m_sizeof(data[cat]))
        data[cat] = ([ relate : ({ with }) ]);
    else if (!sizeof(data[cat][relate]))
        data[cat][relate] = ({ with });
    else
        data[cat][relate] += ({ with });

    save_object(MASTER);
}

/*
 * Function name: find_matching_relate
 * Description  : Return the relationship between 'who' and 'with' in
 *                the category 'cat'.
 * Arguments    : string who - the person who has/claims the relationship
 *                string with - the one 'who' has/claims the relationship with
 *                string cat - the category of the relationship
 *                int claim - 1 for claim, 0 for relationship
 */
public string
find_matching_relate(string who, string with, string cat, int claim)
{
    cat = lower_case(cat);
    who = capitalize(who);
    with = capitalize(with);

    if (claim)
    {
	foreach(string rel: query_claim_relates(who, cat))
	{
            if (member_array(with, query_claim_names(who, cat, rel)) != -1)
		return rel;
	}
    }
    else
    {
	foreach(string rel: query_relate_relates(who, cat))
        {
            if (member_array(with, query_relate_names(who, cat, rel)) != -1)
		return rel;
        }
    }

    return "";
}

/*
 * Function name: remove_claim
 * Description  : Remove a claim from gClaims.
 * Arguments    : string who - the person who claimed the relationship
 *                string with - the person 'who' claimed the relationship with
 *                string cat - the category of the relationship
 *                (variable) string relate - the specific relationship
 * Returns      : string relate
 */
public varargs string
remove_claim(string who, string with, string cat, string relate)
{
    cat = lower_case(cat);
    who = capitalize(who);
    with = capitalize(with);

    if (strlen(relate))
	relate = lower_case(relate);
    else
        relate = find_matching_relate(who, with, cat, 1);

    if (!strlen(relate))
    {
        write("Error, no claim found.\n");
        return "";
    }

    if (sizeof(query_claim_names(who, cat, relate)) > 1)
	gClaims[who][cat][relate] -= ({ with });
    else if (sizeof(query_claim_relates(who, cat)) > 1)
	m_delkey(gClaims[who][cat], relate);
    else if (sizeof(query_claim_cats(who)) > 1)
	m_delkey(gClaims[who], cat);
    else
	m_delkey(gClaims, who);

    save_object(MASTER);

    STATSERV_LOG_EVENT("registry", "Removed");
    SCROLLING_LOG(REG_LOG, "Unregistered Claim: " + 
	who +", "+ with +", "+ cat +", "+ relate);

    return relate;
}

/*
 * Function name: add_relate
 * Description  : Add a new relationship to gRelates.
 * Arguments    : string who - the person who has the relationship
 *                string with - the one 'who' has the relationship with
 *                string cat - the category of the relationship
 *                string relate - the specific relationship
 */
public void
add_relate(string who, string with, string cat, string relate)
{
    mixed data = gRelates[capitalize(who)];
    relate = lower_case(relate);
    with = capitalize(with);
    cat = lower_case(cat);

    if (!m_sizeof(data))
        gRelates[who] = ([ cat : ([ relate : ({ with }) ]) ]);
    else if (!m_sizeof(data[cat]))
        data[cat] = ([ relate : ({ with }) ]);
    else if (!sizeof(data[cat][relate]))
        data[cat][relate] = ({ with });
    else
        data[cat][relate] += ({ with });

    save_object(MASTER);
}

/*
 * Function name: remove_relate
 * Description  : Remove a relationship from gRelates and move the matching
 *                relationship to gClaims.
 * Arguments    : string who - the person who has the relationship
 *                string with - the one 'who' has the relationship with
 *                string cat - the category of the relationship
 *                string relate - the specific relationship
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_relate(string who, string with, string cat, string relate)
{
    cat = lower_case(cat);
    who = capitalize(who);
    with = capitalize(with);

    if (strlen(relate))
	relate = lower_case(relate);
    else
        relate = find_matching_relate(who, with, cat, 0);

    if (!strlen(relate))
        return 0;

    /* Find the matching relate before deleting the first one */
    string cat2 = matching[cat];
    string relate2 = find_matching_relate(with, who, cat2, 0);

    /* Failsafe. */
    if (!strlen(relate2))
        return 0;

    if (sizeof(query_relate_names(who, cat, relate)) > 1)
        gRelates[who][cat][relate] -= ({ with });
    else if (sizeof(query_relate_relates(who, cat)) > 1)
        m_delkey(gRelates[who][cat], relate);
    else if (sizeof(query_relate_cats(who)) > 1)
        m_delkey(gRelates[who], cat);
    else
        m_delkey(gRelates, who);

    /* Now remove the matching relationship. */
    if (sizeof(query_relate_names(with, cat2, relate2)) > 1)
        gRelates[with][cat2][relate2] -= ({ who });
    else if (sizeof(query_relate_relates(with, cat2)) > 1)
        m_delkey(gRelates[with][cat2], relate2);
    else if (sizeof(query_relate_cats(with)) > 1)
        m_delkey(gRelates[with], cat2);
    else
        m_delkey(gRelates, with);

    STATSERV_LOG_EVENT("registry", "Removed");
    SCROLLING_LOG(REG_LOG, "Unregistered Relation: " + 
	who +", "+ with +", "+ cat +", "+ relate);

    /* And move the matching relationship to claim. */
    add_claim(with, who, cat2, relate2);
    return 1;
}

/*
 * Function name: check_status
 * Description  : Check to see the status of a particular combination.
 * Arguments    : string who - the person who has/claims the relationship
 *                string with - the one 'who' has/claims the relationship with
 *                string cat - the category of the relationship
 *                string relate - the specific relationship
 * Returns      : 3 - claim already exists
 *                2 - relationship already exists
 *                1 - matching claim exists, and is eligible for
 *                    upgrade to relationship if this combination
 *                    is registered
 *                0 - no claim, no relationship and no matching claim
 */
public int
check_status(string who, string with, string cat, string relate)
{
    cat = lower_case(cat);
    who = capitalize(who);
    with = capitalize(with);
    relate = lower_case(relate);

    // Claim already exists
    if (member_array(with, query_claim_names(who, cat, relate)) != -1)
        return 3;

    // Relationship already exists
    if (member_array(with, query_relate_names(who, cat, relate)) != -1)
        return 2;

    string cat2 = matching[cat];

    // Other person's claim exists
    if (member_array(cat2, query_claim_cats(with)) != -1)
    {
        string *valid = m_relates[cat][1];

	foreach(string rel: query_claim_relates(with, cat2))
        {
	    if (member_array(rel, valid) == -1)
		continue;

            // Looking for ([ with : ([ cat : ([ oneofrel : ({ who }) ]) ]) ])
            if (member_array(who, query_claim_names(with, cat2, rel)) != -1)
                return 1;
        }
    }

    // No claim, no relationship exists
    return 0;
}

/*
 * Function name: check_relate
 * Description  : Inputs for the relationship if not given at first.
 *                Finishes registering from do_register
 * Arguments    : string who - the one registering
 *                string with - the one that 'who' claims a relationship with
 *                string cat - the category of the relationship
 *                string relate - the specific relationship
 */
public void
check_relate(string who, string with, string cat, string relate)
{
    object ob;
    string cat2, relate2;

    switch(check_status(who, with, cat, relate))
    {
    // Already a claim
    case 3:
        write("The claim of " + relate + " to " + with +
            " already exists. " + with + " must also register " +
            "to turn your claim into a confirmed relationship.\n");
        break;

    // Already a relationship
    case 2:
        write("The relationship of " + relate + " to " + with +
            " already exists.\n");
        break;

    // Matching claim found.
    case 1:
        // Get player's desired relationship.
        add_relate(who, with, cat, relate);
        // Move other player's claim to relationship.
        cat2 = matching[cat];
        relate2 = remove_claim(with, who, cat2);
        add_relate(with, who, cat2, relate2);

        write("You have registered your relationship of " + relate +
	    " to " + with + ".\n");

        if (ob = present("av_registry_seal", TP))
        {
            ob->remove_object();
            write("The seal is now affixed to your proof of registration.\n");
            STATSERV_LOG_EVENT("registry", "Added");
            SCROLLING_LOG(REG_LOG, "Registered Relation: " +
		who +", "+ with +", "+ cat +", "+ relate);
        }

        if (!present(PROOF_ID, TP))
            proof("proof");

	say(QCTNAME(TP) + " has registered a relationship.\n");
        update_proof(who, with);
        break;

    // No matching claim.
    case 0:
        // Add player's desired relation as a claim.
        add_claim(who, with, cat, relate);
        write("You have registered your claim of " + relate +
	    " to " + with + ".\n");

        if (ob = present("av_registry_seal", TP))
        {
            ob->remove_object();
            write("The seal is now affixed to your proof of registration.\n");
            STATSERV_LOG_EVENT("registry", "Added");
            SCROLLING_LOG(REG_LOG, "Registered Claim: " +
		who +", "+ with +", "+ cat +", "+ relate);
        }

        if (!present(PROOF_ID, TP))
            proof("proof");

        say(QCTNAME(TP) + " has registered a claim.\n");
        update_proof(who, with);
        break;

    default:
        write("Something went wrong. Please make a bug report.\n");
        break;
    }
}

/*
 * Function name: do_register
 * Description  : Begin the process to register a claim or relationship
 * Arguments    : string str - as entered by the player, should
 *                be in the format: <category> [relationship] <name>
 * Returns      : 1 if successful, 0 if not
 */
public int
do_register(string str)
{
    string who, with, cat, relate;

    NF("Register <category> [relationship] <name>.\n");
    if (!strlen(str))
        return 0;

    if (!present("av_registry_seal", TP))
    {
        NF("You must purchase a seal before you may register.\n");
        return 0;
    }

    if (sscanf(str, "%s %s %s", cat, relate, with) != 3)
	return 0;

    who = capitalize(TP->query_real_name());
    with = capitalize(with);
    cat = lower_case(cat);
    relate = lower_case(relate);

    if (!SECURITY->exist_player(with))
    {
        write(with + " doesn't exist.\n");
#ifdef REALPLAYERS
        return 1;
#else
        write("Proceeding anyways.\n");
#endif
    }

    if (member_array(cat, cats) == -1)
    {
	write("No such relationship category. Available categories are: "+
	    COMPOSITE_WORDS(cats) + ".\nPlease read the sign or instructions "+
	    "for more help.\n");
	return 1;
    }

    check_relate(who, with, cat, relate);
    return 1;
}

/*
 * Function Name: unregister
 * Description  : The process of unregistering a previously registered
 *                claim or relationship. Unregisters it and moves any
 *                matching relationship to the claim status.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
unregister(string str)
{
    string who, with, cat, relate;

    if (!strlen(str) ||
	(sscanf(str, "%s %s %s", cat, relate, with) != 3))
    {
	NF("Unregister <category> <relationship> <name>.\n");
	return 0;
    }

    who = capitalize(TP->query_real_name());
    with = capitalize(with);
    cat = lower_case(cat);
    relate = lower_case(relate);

    switch(check_status(who, with, cat, relate))
    {
    case 3:
        if (!strlen(remove_claim(who, with, cat, relate)))
        {
            // Shouldn't happen, but just to be sure.
            write("Error, no relationship found!\n");
	    break;
        }

	write("Your claim of being the " + relate + " of " + with +
	    " is unregistered.\n");
	say(QCTNAME(TP) + " unregisters a claim.\n");
	update_proof(who, with);
        break;

    case 2:
        if (!remove_relate(who, with, cat, relate))
        {
            // Shouldn't happen, but just to be sure.
            write("Error, no relationship found!\n");
	    break;
        }

	write("Your relationship as the " + relate + " of " + with +
	    " is unregistered.\n");
	say(QCTNAME(TP) + " unregisters a relationship.\n");
	update_proof(who, with);
        break;

    default:
	write("There is no such relationship or claim to unregister.\n");
	break;
    }
    return 1;
}

/*
 * Function name: list
 * Description  : Lists the relationships and claims for a specific
 *                person, the names of the people with registered claims
 *                and relationships or the claims made of the person
 *                listing.
 * Arguments    : string str - as entered by the player, either a name,
 *                'names' or 'claims'
 * Returns      : 1 if successful, 0 if not
 */
public int
list(string str)
{
    if (!strlen(str))
    {
        notify_fail("List <name>/claims?\n");
        return 0;
    }

    if (str == "claims")
    {
	int counter;
        string name = capitalize(TP->query_real_name());

	foreach(string who: sort_array(m_indices(gClaims)))
	{
	    foreach(string cat: sort_array(m_indices(gClaims[who])))
            {
		foreach(string rel: sort_array(m_indices(gClaims[who][cat])))
                {
		    if (member_array(name, gClaims[who][cat][rel]) != -1)
                    {
                        counter++;
                        write(who + " claims to be your " + rel + ".\n");
                    }
                }
            }
        }

        if (!counter)
            write("No claims have been made against you.\n");

        return 1;
    }

    if (str == "names")
    {
	write("Choose a specific name to list.\n");
	return 1;
#if 0
        string *arr = sort_array(query_claims());
	int size = sizeof(arr);

        if (size > 1)
            write(COMPOSITE_WORDS(arr) +" have registered claims.\n");
        else if (size == 1)
	    write(arr[0] + " has registered claims.\n");
        else
            write("No claims have been registered.\n");

        arr = sort_array(query_relates());
	size = sizeof(arr);

        if (sizeof(arr) > 1)
	    write(COMPOSITE_WORDS(arr) +" have registered cynredes.\n");
        else if (size == 1)
	    write(arr[0] + " has registered cynredes.\n");
        else
	    write("No cynredes have been registered.\n");

        return 1;
#endif
    }

    str = capitalize(str);
    if (!m_sizeof(gClaims[str]))
    {
        write("No claims found for " + str + ".\n"); 
    }
    else foreach(string cat: sort_array(m_indices(gClaims[str])))
    {
	foreach(string rel: sort_array(m_indices(gClaims[str][cat])))
	{
	    foreach(string who: sort_array(gClaims[str][cat][rel]))
		write(str +" claims to be the "+ rel +" of "+ who +".\n");
	}
    }

    if (!m_sizeof(gRelates[str]))
    {
        write("No confirmed cynredes found for " + str + ".\n"); 
    }
    else foreach(string cat: sort_array(m_indices(gRelates[str])))
    {
	foreach(string rel: sort_array(m_indices(gRelates[str][cat])))
	{
	    foreach(string who: sort_array(gRelates[str][cat][rel]))
		write(str +" is the "+ rel +" of "+ who +".\n");
	}
    }

    return 1;
}

/*
 * Function name: proof
 * Description  : Gives a piece of paper with 'proof of registration'
 *                to those who request it and are registered.
 * Arguments    : string str - as entered by the player, should be 'proof'
 * Returns      : 1 if successful, 0 if not
 */
public int
proof(string str)
{
    if (str != "proof")
    {
        notify_fail("Request proof?\n");
        return 0;
    }

    string name = capitalize(TP->query_real_name());

    if (!gClaims[name] && !gRelates[name])
    {
        write("There are no registrations in your name.\n");
        return 1;
    }
    
    if (present(PROOF_ID, TP))
    {
        write("You already carry proof of registration!\n");
        return 1;
    }

    object proof = clone_object(PROOF);
    proof->move(TP);
    proof->update_list();

    write("You are handed proof of registration.\n");
    return 1;
}

/*
 * Function name: init
 * Description  : Adds the verbs to a player entering the room.
 */
public void
init(void)
{
    ::init();

    add_action(list,        "list");
    add_action(do_register, "register");
    add_action(unregister,  "unregister");
    add_action(proof,       "request");
}
