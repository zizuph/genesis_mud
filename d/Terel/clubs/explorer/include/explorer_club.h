/* 
 * Default inherit file for the EXPLORER Club of Terel
 * 
 * Tomas Dec. 1999
 */


#ifndef EXPLORER_DEFS
#define EXPLORER_DEFS


#define HERE                 "/d/Terel/clubs/explorer/"
#define DOC_DIR              HERE + "doc/"
#define OBJ_DIR              HERE + "obj/"
#define GUILDOBJ             HERE + "explorer_ring"


#define EXPLORER_RING           "_explorer_ring"
#define EXPLORER_LOG           HERE + "explorer_log"
#define EXPLORER_PROP          "_live_i_am_explorer"
#define LEADER_PROP            "_is_explorer_leader"
#define EXPLORER_SKILL         139040
#define EXPLORER_SOUL          HERE + "explorer_club_soul"
#define EXPLORER_SUBLOC        "_terel_explorer_subloc"

#define IS_MEMBER(o)      ((o)->query_prop(EXPLORER_PROP))
#define IS_LEADER(l)      ((l)->query_prop(LEADER_PROP))


/*
string *figures = m_indices(figure_type);

mapping query_figure_map()
{
    return figure_type;
}
*/

/* No definitions below this line */
#endif EXPLORER_DEFS
