/* standard defines for the Mystic Club area */
#define MCLUB_DIR            "/d/Calia/zima/mclub/"
#define OBJ_DIR              MCLUB_DIR+"objects/"
#define NPC_DIR              MCLUB_DIR+"monsters/"
#define WEAPON_DIR           MCLUB_DIR+"weapons/"
#define ARMOUR_DIR           MCLUB_DIR+"armours/"
#define ROOM_DIR             MCLUB_DIR+"rooms/"
#define SPECIAL_DIR          MCLUB_DIR+"specials/"
#define MCLUB_SOUL           SPECIAL_DIR+"mclub"
#define OUTSIDE_CONNECTION   "/d/Calia/zima/argos/nwterr/rooms/r2"
#define INCENSE_CLOUD        "_mclub_sanct_incense_cloud"
#define INCENSE_QTY          "_mclub_qty_of_incense"
#define KNEELING_OBJ         "_mclub_sanct_kneeling_obj"
#define MCLUB_ROBE           "_mclub_robe"
#define MCLUB_ALB            "_mclub_alb"
#define MCLUB_MANTLE         "_mclub_mantle"
#define MCLUB_BEADS          "_mclub_beads"
#define MCLUB_LAYOBJ         "_mclub_layhands_object"
#define MCLUB_LAYOBJ_FNPROP  "_mclub_layobj_fname_prop"
#define MCLUB_LAYOBJ_SPROP   "_mclub_layobj_second_prop"
#define MCLUB_LAYOBJ_FILE    OBJ_DIR+"layobj.c"
#define BELLTOWER_KEY_NUM    61467
#define MCLUB_BTKEY       "_mclub_btkey"
#define GATE_KEY_NUM         61468
#define MCLUB_GATEKEY        "_mclub_gatekey"
#define MCLUB_MEMLIST        MCLUB_DIR+"specials/memlist.txt"
 
/* InMClub - this function checks to see if a player is a member   */
/* of the club by looking for the command soul of club members     */
int
InMClub(object Tp)
{
    if (member_array(MCLUB_SOUL, Tp->query_cmdsoul_list()) < 0)
      return 0;
    else
      return 1;
}
