#include "setup.h"

void DrawLogo(void){
	printf( "+======================================================================+\n"
		"|									|\n"
		"|	Beelzebub - An Automatically Malware Classification System	|\n"
		"|									|\n"
		"+======================================================================+\n");

	printf( "\n"
		". 　 　 　 　　 }＼　　　　　　　　　　　　　　　　　　　　　　　　　　 　　　　　 -‐ ￢	\n"
		"　 　 　 　 　　'　 ヽ　　　　　　　　　　　　　　　　　‌　　　　　　　　,　　´ 　　　 ／‌	\n"
		"　　　　　　　　 ', 　 ＼　　　　　　　‌　　‌‌‌‌　　　　　　‌　　　　　‌　 '　 　 　 　 　／‌	\n"
		"　　　　　　　　　′　　＼ 　 　 　　　 ‌‌　‌‌ 　　　‌‌　　　　,.　'′　　　　 　　 ／		\n"
		"　　　　 　 　　 　゛ ‌‌　 　　＼　　 　 　‌‌‌‌‌ 　　　‌　‌　　 ‌‌／　　‌‌　　‌　　‌‌　　　∠ - ァ‌		\n"
		"　 　 　 　 　 　　、ヽ　‌‌　 　　ヽ　 ＿__　 　　　‌‌ ／　‌‌　　　　　　　　／　　／		\n"
		".　　　　　 　 　 　＼ ＼　　　　y′ ‌　 ｀＞‌┐‌ ‌‌　‌‌ 　 　rヘ‌、_‌‌,‌‌..‌ -‐'′　／‌		\n"
		"　　　 　 　 　 { 下ﾐヽ　　r-√/ 　　 ／　 　＞‐ｘ‌‌‌　 /　‌‌‌r' }　 ‌‌r‌ﾍ、＿_‌‌‌			\n"
		"　　r'⌒ヽ 　 　｀Y＾ ド=斗 个ー一 ' ス　／　/⌒／　/ ‌‌/　 ﾉ-ト-─ﾚ'＾〉‌‌‌			\n"
		"　　}　　 ｨ〉_　　　゛rﾍ　　　 l　‌‌　 ／, ‌‌く /　／ ￣　　ｲ 厶イ＾>'　　　{　/		\n"
		"　　 >､_　∠_ヽ　　 )/＾ヽ　｜‌‌　/ /　　 Ｖ　　　　／ ﾉ ' r‐' ´ 　　　∧ {‌‌		\n"
		"　　{「/ﾊーﾍ ヽ　　 { 　 　 Yvﾊr' 　 　　} ＿r＜｀ヽ{＿广ﾚァ　　　 ヾﾐﾊ_ﾉ}‌			\n"
		"　 　 j｣　Y´ﾍ　　 　 ゝ　　 价トﾍ、 　 ,ｲト-辷＿＿ ｀ヽ∧._/ヽ ‐z_　 ゝ-く＿ﾉ}‌‌		\n"
		".　　　　　 Yr＜ミｰく /｀,ﾆﾌ厶‌‌{ ＬﾐT升く　　 ﾌ＾Y ⌒ト-}ﾊ仏'＾ﾘ 二≧ ＼ 匸´		\n"
		". 　 　 　 　 辷ン⌒ '′| 爪 {ﾊ｀ﾌｲ 〉廴ﾉ　r‌‌Ｌ._介ーﾍ　 ﾉｼヘ>､｀ヾ三ミ､ ￣´		\n"
		"　　　　　　　　ﾏﾍ　　　| [ﾌ｀Ｙﾍﾆ//;{ 　 〉人　 Vー─ 〈{、 　 }/─-く≦ヘ		\n"
		"　　　 　 　 　 　ﾞｖ', 　 ∧!　,ﾉ　 /ｲ　ゝ く´ 　}ｰ１───ヘ、 ＼─‐-ﾍ三ﾍ		\n"
		".　　　　　　 　 　 ヾ, 　｝-仄⌒}' ﾄ{ 〈 　 ﾉ /＾′ ｉー─‐──ﾍ　 ＼─-}ﾄミﾍ		\n"
		".　　　　　 　 　 　ノー勹　　 Ｙ＾ﾉ7⌒Y ／　 　 　Yー───,ハ 　 }--､}ト-ド､		\n"
		"　　　 　 　　　　ﾉﾍ勹ﾌ 　 　 ﾚ'ﾌ＾ー'＾ブミx 　　　 Ｖー──{　′ 厶--ﾍいﾊ		\n"
		".　　　　 　 　　 ′　〈{ 　 　 //ゝー一＜ r-ヘ、 　 ヽー──i｀T´─- ､ jＹ1ｌ|		\n"
		"　　　　　　　　　　　　 　 　/'′　　　　 　｀Yｰﾍ、　　 Y二二」　{─- ､ ｀ﾄハﾘ		\n"
		"　　　　　　　　　 　 　　 ／ 　　　　　　　　厶-イ　　　 }ー-　ゝ-ﾍ-､ 　V 从		\n"
		"　　　　　　　　　　　　　 　 　 　 　　　 　rく　　,ﾊ 　 　 }ﾆﾐ　 { i⌒ﾘ　ヽ;ﾊV		\n"
		"　　　　　　　　　 　 　　　∠ミーヘrヘｨ'′ Ｌrﾍﾘ　　 rfヘ、＼`く/⌒>'　jﾉ			\n"
		"　　　　　　　　　　　 　ｒく　　入＿_Ｌ.　ゝ‐^　　　f廴厶 ヽ_} _厶-{_厂{			\n"
		"　　　　　　 　 　 ､＿rヘ _>ｲ　　　　　　　　　　ミ≧彡ｸ}┘ 　 　 j、　ゝ			\n"
		"　　　　　　　 ／ﾍノrー'＾ヽ Ｌ._　　　　　　　　　　￣ '´　　　　ｒ-久 Y ﾚ- ､		\n"
		"　　　　　　　　 　 　　 　 　｀￣　　　　　　　　　　　　　　　　　´　　｀＾V⌒ヽ		\n"
	);
}

			
int IsNumberOfCommandlineValRight(int num){
	if(num > 2){
		printf("Error (argv) : Too many arguments\n");
		printf("Usage : beelzebub MalwareName\n");

		exit(EXIT_FAILURE);

	}else if(num < 2){
		printf("Error (argv) : Too few arguments\n");
		printf("Usage : beelzebub MalwareName\n");

		exit(EXIT_FAILURE);

	}else{
		return 0;
	}
}


int SetupMalwareFile(	unsigned char *name,
			FILE *fp, 
			unsigned char *buf){
	int size;

	fp = fopen(name, "rb");
	if(fp == NULL){
		printf("Error (fopen) : cannot open file '%s'\n", name);
		exit(EXIT_FAILURE);
	}

	size = fread(buf, 1, BUFFERSIZE, fp);
	if(size < 0){
		printf("Error (fread) : cannot read binaries from '%s'\n", name);
		exit(EXIT_FAILURE);
	}

	return size;
}
	

void SetupBeelzebub(int num,
		     unsigned char *name,
		     FILE *fp,
		     unsigned char *buf){
	int size;

	DrawLogo();

	if(IsNumberOfCommandlineValRight(num) == 0){
		size = SetupMalwareFile(name,
					fp,
					buf);
	}else{
		printf("Error (SetupBeelzebub) : Failed to setup Beelzebub\n");
		exit(EXIT_FAILURE);
	}
}

