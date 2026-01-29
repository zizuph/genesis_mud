#define DIR "/d/Khalakhor/guilds/blademasters/kdefend/"
#define CACHE_MEMBER_OBJ (DIR + "member")
#define MEMBER_CACHE (DIR + "skillcache")
#define MEMBER_FILE(x) (DIR + "members/" + x[0..0] + "/" + x)
#undef DEBUG(x) (find_player("rhyn")->catch_msg(x))
