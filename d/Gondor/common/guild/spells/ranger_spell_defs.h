// This define will disable the old ranger spells.
#define NEW_RANGER_MAGIC   1
        /* Numbers:       0    1    2    3    4    5    6    7    8    9  */
#define RSPELL_CODENAME ({"sp","hl","sg","hf","hp","hm","rh","rc","rp","rm",\
          "de","ru","nv","cl","st","li","da","dv","re","he","dp","cp","vi"})

#define RSPELL_NAME ({ "whistle", "herblore","speedgrow","herbfind",\
          "preserve","herbmastery","heatresist","coldresist","poisonresist",\
          "magicresist","detect","elbereth","nightvision","cloak","stealth",\
          "light","darkness","darkvision","rest","heal","diagnose","cleanse",\
          "vitalize" })

#define RSPELL_LEVEL ({ 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 5, 0, 0, 0, 0, 10, 15, 0, 20, 0})
#define RSPELL_FUNC(x) "do_"+RSPELL_NAME[x]+"_spell"
#define MAX_LEVELS ({ 20, 100, 60, 60 })

#define RSPELL_DESC ({ "summon a carrier pigeon", "identify a herb",\
          "speed growth of herbs","find herbs easier", "preserve a herb from decay",\
          "increased herbalism skill", "tolerate heat better",\
          "tolerate cold better", "resist poison effects", "resist effects of magic",\
          "sense if someone is evil", "chase away Undead", "see in darkness outside",\
          "increases hiding ability", "become more stealthy", "make magical light",\
          "make magical darkness", "see better in darkness", "rest fatigue",\
          "heal wounds", "check someones poisoning","cleanse away someone's poisoning",\
          "rest and heal someone" })
