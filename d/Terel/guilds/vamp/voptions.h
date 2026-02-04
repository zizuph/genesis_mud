#ifndef VOPTIONS_INCLUDED
#define VOPTIONS_INCLUDED

#ifndef BIT
#define BIT(x)  (1 << x)
#endif

#define VOPT_NOTIFY_LIGHT          BIT(0)
#define VOPT_NOTIFY_SUNLIGHT       BIT(1)
#define VOPT_NOTIFY_THIRST         BIT(2)
#define VOPT_NOTIFY_LOGIN          BIT(3)
#define VOPT_AUTOMELD              BIT(4)
#define VOPT_VAMPIRE_RACE          BIT(5)
#define VOPT_DVIS                  BIT(6)
#define VOPT_INTRO_TITLE           BIT(7)
#define VOPT_INTRO_PTITLE          BIT(8)
#define VOPT_VAMP_ATTACKS          BIT(9)
#define VOPT_BRIEF_ATTACKS         BIT(10)
#define VOPT_VSAY                  BIT(11)
#define VOPT_DRAIN_PAST_DEATH      BIT(12)
#define VOPT_SUPPRESS_DARK         BIT(13)
#define VOPT_DRAIN_SKILL_MODE      BIT(14)
#define VOPT_DRAIN_RESIST_MODE     BIT(15)
#define VOPT_DRAIN_HASTE_MODE      BIT(16)
#endif
