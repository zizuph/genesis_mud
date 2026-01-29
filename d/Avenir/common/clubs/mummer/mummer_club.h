// Mummer club defines. 
// Also has mappings and strings used commonly
// by the soul and the mummer objects.

#ifndef MUMMER_DEFS
#define MUMMER_DEFS

/* Alarm controlling performance sequences */
#define MIME_ALARM           "_avenir_mummer_alarm"

/* Add defs for performance indices below */
#define EAT_INDEX            "_mummer_fireat_index"
#define LEVI_INDEX           "_mummer_levitation_index"
#define SCARF_INDEX          "_mummer_scarf_index"
#define SWALLOW_INDEX        "_mummer_swallow_index"
#define TWIST_INDEX          "_mummer_twist_index"
#define WALL_INDEX           "_mummer_wall_index"

#define HERE                 "/d/Avenir/common/clubs/mummer/"
#define DOC_DIR              HERE + "doc/"
#define OBJ_DIR              HERE + "obj/"
#define GUILDOBJ             HERE + "mum_cap"

#define MIME_MESSAGE          "You're too busy pantomiming to speak!\n"

#define MUMMER_CAP           "_avenir_mummer_cap"
#define MUMMER_LOG           "/d/Avenir/log/mummer_log"
#define MUMMER_PROP          "_live_i_am_mummer"
#define MUMMER_SKILL         139040
#define MUMMER_SOUL          HERE + "mummer_soul"
#define MUMMER_SUBLOC        "_avenir_mummer_subloc"

#define IS_MEMBER(o)      ((o)->query_prop(MUMMER_PROP))
#define ADD_A_LEVEL(o)    (o->set_skill(MUMMER_SKILL, (1 + (o->query_skill(MUMMER_SKILL)))))

public mapping 
figure_type = ([       
        "cat"      : ({ "cat", "This looks just like a small cat! "+
                        "The tail portion even seems to flick idly "+
                        "about" }),
        "bicorn"   : ({ "bicorn", "This is a horse-like creature with "+
                        "two horns" }),
        "dog"      : ({ "dog", "This very long, short-legged figure "+
                        "strongly resembles a dog" }),
        "dogcow"   : ({ "dogcow", "Hey, this looks just like the dogcows "+
                        "that dwell in the orchard near the Glade of Beg"+
                        "innings" }),
        "dragon"   : ({ "dragon", "This looks very much like a dragon in "+
                        "flight. The barbed tail trembles as you hold the "+
                        "figure in your hand" }),
        "frog"     : ({ "frog", "This small figure resembles a cute "+
                        "little frog. It seems almost ready to hop "+
                        "right out of your hand" }),
        "horse"    : ({ "horse", "This figure remarkably resembles a "+
                        "horse in fluid motion" }),
        "monkey"   : ({ "monkey", "This monkey figure is so life-like "+
                        "that you wouldn't be surprised if it started "+
                        "chittering at you" }),
        "mouse"   :  ({ "mouse", "A cute little mouse figure with over-"+
                        "large ears and oddly humanoid hands" }),
        "pig"     :  ({ "pig", "This pig figure stands upon its hind-"+
                        "legs. Its face is surprisingly genial" })   
]);  

string *figures = m_indices(figure_type);

mapping query_figure_map()
{
    return figure_type;
}

/* No definitions below this line */
#endif MUMMER_DEFS
