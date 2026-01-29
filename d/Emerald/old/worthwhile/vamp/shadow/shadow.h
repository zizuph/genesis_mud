#define BLOOD        1
#define DARKVISION   2
#define DEATH        4
#define SUNLIGHT     8
#define VAMP_DESC    16
#define VAMP_HEAL    32
#define VAMP_MOVE    64
#define VAMP_SH      128
#define VAMP_STATS   256
#define WIZSTAT_VAMP 512

// Prototypes:
int         sunlight_res();

int         query_effective_vamp_stat();
int         query_max_vamp_stat();
int         query_excess_thirst();
int         query_stat(int stat);
int         query_max_thirst();
int         query_vamp_age();
int         query_power_offset();
int         query_base_vamp_stat();
int         query_vamp_stat();
int         query_sunlight_modifier();
int         query_vamp_covenmaster();
int         query_thirst_modifier();
int         query_guild_leader_occ();
int         query_vamp_option(int opt);
int         query_mana_drain();
int         query_vamp_generation();
varargs int thirst();
varargs int query_thirst();
varargs int query_sunlight_level(object where);
void        add_thirst(int amnt);
void        reset_darkvision();
void        update_title();
void        add_mana_drain(int amnt);
void        set_vamp_coven(string coven);
void        break_vamp_drain();
string      query_vamp_coven();
string      query_sire();
