/*
 * /d/Genesis/homes/relation.h
 *
 * This file contains the definitions that are used to keep track of all
 * relations between players in Genesis.
 *
 * /Mercade, 20 December 1993
 *
 * Revision history:
 */

#ifndef RELATION_DEFINITIONS
#define RELATION_DEFINITIONS


/*
 * RELATION_DIR is the directory with the stuff for relations.
 */
#define RELATION_DIR           ("/d/Genesis/homes/")

/*
 * RELATION_SAVE_FILE is the safe-file with the information on relations.
 */
#define RELATION_SAVE_FILE     (RELATION_DIR + "relation_save")

/*
 * RELATION_MASTER is the master object that registers relation matters.
 */
#define RELATION_MASTER        (RELATION_DIR + "relation_master")

/*
 * QUERY_RELATION(string player_name)
 *
 * Return whether player_name has a relationship with one or more other
 * players.
 */
#define QUERY_RELATION(s)      ((int)RELATION_MASTER->query_relation(s))

/*
 * QUERY_RELATION_TYPE(string player_name)
 *
 * Return the type of relation player_name has. The different types of
 * relations are defined below.
 */
#define QUERY_RELATION_TYPE(s) \
    ((string)RELATION_MASTER->query_relation_type(s))

/*
 * QUERY_PARTNERS(string player_name)
 *
 * Returns an array of string with the (lower case) names of all people
 * player_name has a relation with or 0 if the player doesn't have a
 * relation.
 */
#define QUERY_PARTNERS(s)      ((string *)RELATION_MASTER->query_partners(s))

/*
 * QUERY_HAS_RELATION_OF_TYPE(string player_name, int relation_type)
 *
 * Returns whether player_name is involved in a relation of relation_type.
 */
#define QUERY_HAS_RELATION_OF_TYPE(s, t) \
    ((int)RELATION_MASTER->query_has_relation_of_type(s, t))

/*
 * QUERY_HAVE_A_RELATION(string player_name_1, string player_name_2)
 *
 * Returns whether player_name_1 and player_name_2 have a relation with
 * eachother. This does not mean they are the only two members of the
 * relation.
 */
#define QUERY_HAVE_A_RELATION(s1, s2) \
    ((int)RELATION_MASTER->query_have_a_relation(s1, s2))

/*
 * ADD_RELATION(string *player_names, int relation_type)
 *
 * Adds a relation to the master meaning that player_names have a relation
 * of relation_type. The relation types are defined below.
 */
#define ADD_RELATION(as, s)    ((int)RELATION_MASTER->add_relation(as, s))

/*
 * REMOVE_RELATION(string player_name)
 *
 * Removes the relation player_name is involved in from the list of known
 * relations.
 */
#define REMOVE_RELATION(s)     ((int)RELATION_MASTER->remove_relation(s))

/*
 * REMOVE_PLAYER_FROM_RELATION(string player_name)
 *
 * Remove player_name from the relation he is involved in. If there are only
 * two people in the relation, the entire relation is removed.
 */
#define REMOVE_PLAYER_FROM_RELATION(s) \
    ((int)RELATION_MASTER->remove_player_from_relation(s))

/*
 * CHANGE_RELATION_TYPE(string player_name, relation_type)
 *
 * Change the relation player_name is involved in to relation_type. The types
 * that are possible are defined below.
 */
#define CHANGE_RELATION_TYPE(s, t) \
    ((int)RELATION_MASTER->change_relation_type(s, t))

/*
 * QUERY_POSSIBLE_RELATION_TYPES
 *
 * Returns an array of string with all possible relation types.
 */
#define QUERY_POSSIBLE_RELATION_TYPES \
    ((string *)RELATION_MASTER->query_possible_relation_types())

/*
 * GET_ALL_RELATIONS
 *
 * Returns all maternal relations that are in the system. The structure of
 * this mixed is as follows
 *
 * ({ string:relation_type, ({ string:member1, string:member2 }),
 *    string:relation_type, ({ string:member1, string:member2 })
 * })
 *
 * example:
 *
 * ({ "marriage", ({ "kithkanan", "rae"  }),
 *    "marriage", ({ "remo",      "bixi" })
 * })
 */
#define GET_ALL_RELATIONS      (RELATION_MASTER->get_all_relations())

/*
 * DUMP_RELATIONS
 *
 * This routine dumps all relations stored into the master to the currently
 * active wizard. If this_interactive() isn't a wizard, nothing will happen.
 */
#define DUMP_RELATIONS         (RELATION_MASTER->dump_relations())


#endif RELATION_DEFINITIONS
/*
 * Do not add any definitions below this line!
 */
