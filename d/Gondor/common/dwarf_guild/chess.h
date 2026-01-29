/*
 * /d/Gondor/common/dwarf_guild/chess.h
 *
 * Copyright (C) Stas van der Schaaf - January 12 1994
 *               Mercade @ Genesis
 *
 * This file contains a set of diagrams with chess-problems. These problems
 * may be solved by players to gain experience. These problems have been
 * taken from educational material distributed by the Royal Netherlands
 * Chess Union.
 */

#define PIECE_NAMES   ({ "k", "q", "r", "b", "n", "p" })
#define BOARD_LETTERS ({ "a", "b", "c", "d", "e", "f", "g", "h" })
#define BOARD_NUMBERS ({ "1", "2", "3", "4", "5", "6", "7", "8" })

/*
 * "problems" is a mixed structure with the problems and solutions.
 * For each problem first the solution is given in a string and then the
 * problem itself follows in as array of string.
 *
 * The white player will handle the pieces in capitals and black will be
 * the lower cased player.
 *
 * The following abbreviations will be used for the pieces:
 *
 * k - king
 * q - queen
 * r - rook
 * b - bishop
 * n - knight
 * p - pawn
 *
 * The chessboard should look like this (opening position):
 *
 * ({ "rnbqkbnr",
 *    "pppppppp",
 *    "........",
 *    "........",
 *    "........",
 *    "........",
 *    "PPPPPPPP",
 *    "RNBQKBNR" })
 *
 * Solutions should be given in algebaric notation and in lowercase. Only
 * the move itself should be mentioned, the name of the piece should be
 * omitted, not whether the a piece is captured. Placing the opponents
 * king in check should be left out also. If a pawn promotes, the name of
 * the piece the pawn is promoted to, should be added.
 *
 * Note that a parser is used that makes the whole solution lower case and
 * removes all characters not in "a..h 1..8 kqrbnp" before comparing. This
 * parsing is done on both the solution given by the player as the solution
 * in the array.
 *
 * Castling will be notated as "0-0" or "0-0-0"
 *
 * Examples: "qd1 f3" (normal move by the queen)
 *           "0-0"    (castling Ke1-g1 or Ke8-g8)
 *           "g7-g8q" (pawn promotes to queen)
 *
 * Note: If the solution is preceded by a # it means that BLACK
 *       is the party to mate in two!
 */

/*
 * This variable currently contains 50 problems.
 */
static private mixed problems =

    ({ "qd6-f6",      /*  0 */

    ({ "..r.rk..",
       "pp..n.pp",
       "...Q....",
       ".....p..",
       "q.B..B..",
       "........",
       "PP.....P",
       "K.R....." }),

       "nd4-b5+",     /*  1 */

    ({ "r...r...",
       "p..n.ppp",
       "..pk....",
       "..Np.n..",
       "...N....",
       ".P......",
       "P..P.PPP",
       "..R.R.K." }),

       "bg4-c8+",     /*  2 */

    ({ "...R....",
       "pkp....p",
       ".pb.....",
       "........",
       ".....NB.",
       "....P..P",
       "PP...qP.",
       ".K......" }),

       "nf5-g7",      /*  3 */

    ({ ".....B.b",
       "........",
       "........",
       ".....N..",
       "........",
       "........",
       "p.K.....",
       "k......." }),

       "qe4-h7",      /*  4 */

    ({ "........",
       "k...P...",
       "........",
       "K.......",
       "....Q...",
       "........",
       "........",
       "........" }),

       "d7-d8n",      /*  5 */

    ({ "........",
       "k..P....",
       "........",
       "K.......",
       "....Q...",
       "........",
       "........",
       "........" }),

       "#ra7-a3",     /*  6 */

    ({ "........",
       "r.......",
       "........",
       "........",
       "........",
       ".p......",
       "PP......",
       "KBk....." }),

       "qb1-e4",      /*  7 */

    ({ "........",
       "R.......",
       "..K.kr.q",
       "...pp...",
       "..pP..P.",
       "b.......",
       "........",
       ".Q......" }),

       "#kf2-g1",     /*  8 */

    ({ "........",
       "......N.",
       "........",
       ".......p",
       "....np.P",
       ".......K",
       ".....k..",
       "........" }),

       "ne4-g5",      /*  9 */

    ({ "........",
       "........",
       "........",
       ".......K",
       "....N...",
       "......N.",
       ".....npn",
       "......k." }),

       "ra8-b8",      /* 10 */

    ({ "R.......",
       "..k..r.r",
       "...p....",
       "...K.p..",
       "........",
       ".R.....p",
       "........",
       "........" }),

       "kd2-e3",      /* 11 */

    ({ "........",
       "..r.rp..",
       "....pN..",
       ".p.bPk.p",
       "..p..P..",
       "P.P...R.",
       ".P.K...P",
       "R......." }),

       "#ra3-d3",     /* 12 */

    ({ "........",
       "Rp...pkp",
       "P.p...p.",
       "....K...",
       "..r.....",
       "r.....P.",
       "...P.P.P",
       ".......R" }),

       "#qh3-f1",     /* 13 */

    ({ "......k.",
       ".....ppp",
       "Pp..p...",
       "..b.....",
       ".....n.N",
       ".Q...P.q",
       "R....P.P",
       "....r.RK" }),

       "nf4-e6+",    /* 14 */

    ({ "..r..k.r",
       ".R......",
       ".....Pb.",
       "p.......",
       ".....N..",
       "..Pp.qB.",
       ".P.....P",
       "......K." }),

       "nf3-g5+",     /* 15 */

    ({ "r...r...",
       "pppq.kpp",
       "..n.....",
       "b...P...",
       "........",
       "B....N..",
       "P.Q..PPP",
       "R.....K." }),

       "#qg7-g3+",    /* 16 */

    ({ "..kr..r.",
       "ppp...q.",
       "....p...",
       "PP.pP..p",
       "...P.p.n",
       "..P....P",
       "...N.P.K",
       "......NQ" }),

       "#rb3-a3+",    /* 17 */

    ({ ".r....k.",
       "..p..ppp",
       "........",
       ".qP.....",
       "R...Q...",
       ".rP..P..",
       "....N.PP",
       "K......R" }),

       "rf6*bf7+",    /* 18 */

    ({ "....rk..",
       "pp...b..",
       "..p.pR.P",
       "....Q.p.",
       "........",
       "q.pB....",
       "P.P.....",
       ".K......" }),

       "qe6-c8+",     /* 19 */

    ({ ".....k..",
       ".....rq.",
       "p.p.Q..R",
       ".p..P...",
       "......p.",
       "P.......",
       ".PP....P",
       ".K.....R" }),

       "nc4-b6+",     /* 20 */

    ({ "kr......",
       "pp..qppp",
       "...b.n..",
       "..p.....",
       "..N..Q..",
       ".PP....P",
       ".....PP.",
       "...R..K." }),

       "#qe2*a2+",    /* 21 */

    ({ "...r.rk.",
       ".p...ppp",
       "..p.....",
       ".....p..",
       ".P......",
       ".PBn..Q.",
       "P...q.PP",
       "KR.....R" }),

       "qf2*a7+",     /* 22 */

    ({ "kr...r..",
       "p.......",
       "........",
       "........",
       ".....p..",
       "..PP...q",
       ".R...Q..",
       "KR......" }),

       "#rg8*g2+",    /* 23 */

    ({ "......rr",
       "p..k....",
       "..npq...",
       "..BQp...",
       ".P..P...",
       "P.N.....",
       ".....PP.",
       "R....RK." }),

       "ne6-g5+",     /* 24 */

    ({ "r......n",
       ".b.q..pk",
       ".p.bN..p",
       "..p..P..",
       "..Bp....",
       ".P.N....",
       "P...QPP.",
       "....R.K." }),

       "qh6-g7+",     /* 25 */

    ({ ".....rk.",
       "...q.r.p",
       ".p..b.pQ",
       "p.p...p.",
       "P...P..P",
       ".PBP....",
       "..P..R..",
       ".....R.K" }),

       "ba6-b7++",    /* 26 */

    ({ "k.r.r...",
       ".......p",
       "BPp..n..",
       "Q....p.p",
       "....p..P",
       ".PqnN.P.",
       "P.......",
       ".K.R...." }),

       "rb1*b6+",     /* 27 */

    ({ "........",
       ".r.....p",
       "kpQ...p.",
       "p...rp..",
       "P.......",
       "........",
       "....bPPK",
       ".R......" }),

       "qf5-f7+",     /* 28 */

    ({ "....r.k.",
       "pp....p.",
       "..p.....",
       "...nnQN.",
       ".P.q....",
       "P......P",
       ".....PP.",
       "....RBK." }),

       "qd1-h5+",     /* 29 */

    ({ "....r..k",
       ".b.n.p..",
       ".q..r.p.",
       "pp.nP.N.",
       "........",
       "BPp...RP",
       ".....PP.",
       ".B.QR.K." }),

       "qd2-h6+",     /* 30 */

    ({ "...r....",
       "......np",
       "pq..n.k.",
       ".p.....p",
       "...Pp..P",
       "..N...P.",
       "PP.Q.RK.",
       "R......." }),

       "rf1*nf8+",    /* 31 */

    ({ "..r..nkr",
       "..qb....",
       "p...p.pQ",
       ".p..P...",
       ".n....PP",
       "........",
       "PPB.....",
       ".K.R.R.." }),

       "qb8-g8+",     /* 32 */

    ({ ".Q......",
       "..p..kpn",
       "...p.bN.",
       "...n...P",
       "......B.",
       "........",
       "r..q.PP.",
       "..R...K." }),

       "be3-h6+",     /* 33 */

    ({ "...r.k.b",
       ".......Q",
       "p....qP.",
       ".p.p.p..",
       "..nP....",
       "....BP..",
       "PP......",
       ".K..R..." }),

       "re5-h5+",     /* 34 */

    ({ "..r.....",
       ".br..p..",
       "pn..pPpk",
       ".p..R...",
       ".P.N..PP",
       ".PP.R...",
       "..BK....",
       "........" }),

       "qd7-e8+",     /* 35 */

    ({ "rk.....r",
       "p..Qbp.p",
       "bq..pN..",
       "........",
       "........",
       "......P.",
       "PP...PBP",
       "..R...K." }),

       "qh5*h6",      /* 36 */

    ({ "r....rk.",
       "pbn.qpp.",
       ".pnbp..p",
       "..ppB.NQ",
       "...P.P.P",
       "..PBP...",
       "PP.N..P.",
       "R...K..R" }),

       "rd6-f6+",     /* 37 */

    ({ "...rrk..",
       ".bq.n.pp",
       "p..R....",
       ".pp..p..",
       "........",
       ".QP.BN..",
       "PP...PPP",
       "...R..K." }),

       "rb5-b8",      /* 38 */

    ({ "......rk",
       "q....p.p",
       "r...pPpQ",
       "pR.pN...",
       "...P....",
       "....P...",
       "P....P.P",
       "......K." }),

       "#ne4-g3+",    /* 39 */

    ({ "r...kb.r",
       "pQpbqppp",
       "........",
       ".B......",
       "...Pn...",
       "..P..n..",
       "PP...PPP",
       "RNB..K.R" }),

       "qe2-h5+",     /* 40 */

    ({ "....B...",
       ".rp..R..",
       "......kp",
       "..n.b.p.",
       "...r....",
       "P.N...P.",
       ".P.qQ..P",
       ".K......" }),

       "e7*f8n+",     /* 41 */

    ({ ".r...n.r",
       ".p.kP.p.",
       ".bpN..q.",
       ".....N..",
       ".p...P..",
       ".......p",
       "PPP.Q.P.",
       ".......K" }),

       "#rc2-c3+",    /* 42 */

    ({ "....rk..",
       ".p....pp",
       "...p.p..",
       "....bP..",
       "....P...",
       ".P.K.NP.",
       ".Pr.Q..P",
       "q..RR..." }),

       "nd4-e6+",     /* 43 */

    ({ ".r...kr.",
       ".qp.b...",
       "p......p",
       "..n.Np.B",
       "..PN.P..",
       ".P......",
       "KB......",
       ".....Q.." }),

       "nd6-f5++",    /* 44 */

    ({ "........",
       ".p..kpp.",
       "r..Npn.p",
       "..B.b...",
       "..b.....",
       "......P.",
       "P...PPKP",
       "...R...." }),

       "qh6-e6+",     /* 45 */

    ({ "..bq.nkb",
       "..p....p",
       "..pp...Q",
       "r....NpN",
       "p..PP...",
       "..P.....",
       "PP....PP",
       ".....RK." }),

       "qc8-f5+",     /* 46 */

    ({ "..Q.....",
       "........",
       "p....Np.",
       ".p.pn...",
       "...N.k.n",
       "P.P.....",
       ".P...K..",
       ".......q" }),

       "rh1-a1+",     /* 47 */

    ({ "Q.......",
       "......q.",
       "..p.....",
       ".....Pp.",
       "....p.P.",
       "b.......",
       "k.K.....",
       ".......R" }),

       "rb1*b7",      /* 48 */

    ({ "Rrk....r",
       ".pq..pp.",
       "..Qp..bp",
       "....p...",
       "..P.P..B",
       ".....P..",
       "..P...PP",
       ".R.....K" }),

       "qa4-c4",      /* 49 */

    ({ "....N.R.",
       ".......K",
       "..pp....",
       ".B.r.k..",
       "Q..b..p.",
       "..NpR.P.",
       "........",
       "..n....." })
    });
