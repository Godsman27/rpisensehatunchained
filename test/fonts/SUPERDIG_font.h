const unsigned char font[96][6] = {
	{0x00,0x00,0x00,0x00,0x00,0x00}, //  
	{0x58,0x5c,0x00,0x00,0x00,0x00}, // !
	{0x00,0x01,0x00,0x00,0x01,0x00}, // "
	{0x00,0x00,0x00,0x00,0x00,0x00}, // #
	{0x5c,0xfe,0x54,0xfe,0x74,0x00}, // $
	{0x00,0x00,0x00,0x00,0x00,0x00}, // %
	{0x70,0x5c,0x54,0x74,0x7c,0x50}, // &
	{0x00,0x01,0x00,0x00,0x00,0x00}, // '
	{0x70,0x7c,0x44,0x00,0x00,0x00}, // (
	{0x44,0x7c,0x70,0x00,0x00,0x00}, // )
	{0x00,0x00,0x00,0x00,0x00,0x00}, // *
	{0x10,0x10,0x70,0x7c,0x10,0x00}, // +
	{0x40,0xc0,0x00,0x00,0x00,0x00}, // ,
	{0x10,0x10,0x10,0x10,0x00,0x00}, // -
	{0x40,0x40,0x00,0x00,0x00,0x00}, // .
	{0x70,0x7c,0x03,0x00,0x00,0x00}, // /
	{0x7c,0x44,0x44,0x44,0x7c,0x1c}, // 0
	{0x04,0x04,0x7c,0x1c,0x00,0x00}, // 1
	{0x74,0x74,0x54,0x54,0x5c,0x00}, // 2
	{0x44,0x54,0x54,0x54,0x7c,0x70}, // 3
	{0x1c,0x10,0x10,0x7c,0x7c,0x00}, // 4
	{0x5c,0x5c,0x54,0x54,0x74,0x00}, // 5
	{0x70,0x7c,0x54,0x54,0x74,0x00}, // 6
	{0x04,0x14,0x14,0x14,0x7c,0x70}, // 7
	{0x70,0x5c,0x54,0x74,0x7c,0x00}, // 8
	{0x5c,0x54,0x54,0x54,0x7c,0x1c}, // 9
	{0x50,0x50,0x00,0x00,0x00,0x00}, // :
	{0x50,0xd0,0x00,0x00,0x00,0x00}, // ;
	{0x18,0x18,0x24,0x42,0x00,0x00}, // <
	{0x28,0x28,0x28,0x28,0x00,0x00}, // =
	{0x42,0x24,0x18,0x18,0x00,0x00}, // >
	{0x04,0x14,0x54,0x54,0x1c,0x1c}, // ?
	{0xf8,0x04,0x74,0x74,0x54,0x54}, // @
	{0x70,0x7c,0x14,0x14,0x3c,0x00}, // A
	{0x7c,0x74,0x54,0x54,0x7c,0x00}, // B
	{0x70,0x7c,0x44,0x44,0x44,0x44}, // C
	{0x70,0x7c,0x44,0x44,0x48,0x70}, // D
	{0x70,0x7c,0x54,0x54,0x54,0x44}, // E
	{0x70,0x7c,0x14,0x14,0x14,0x04}, // F
	{0x70,0x7c,0x44,0x44,0x54,0x74}, // G
	{0x70,0x7c,0x10,0x10,0x7c,0x00}, // H
	{0x70,0x7c,0x00,0x00,0x00,0x00}, // I
	{0x60,0x40,0x40,0x40,0x7c,0x70}, // J
	{0x7c,0x70,0x10,0x1c,0x70,0x00}, // K
	{0x70,0x7c,0x40,0x40,0x40,0x60}, // L
	{0x70,0x7c,0x04,0x04,0x7c,0x04}, // M
	{0x70,0x7c,0x04,0x04,0x04,0x7c}, // N
	{0x70,0x7c,0x44,0x44,0x44,0x7c}, // O
	{0x70,0x7c,0x24,0x24,0x3c,0x00}, // P
	{0x7c,0x44,0x44,0x44,0x7c,0x00}, // Q
	{0x7c,0x74,0x14,0x14,0x3c,0x00}, // R
	{0x5c,0x5c,0x54,0x54,0x74,0x00}, // S
	{0x04,0x04,0x7c,0x74,0x04,0x00}, // T
	{0x70,0x7c,0x40,0x40,0x40,0x7c}, // U
	{0x70,0x7c,0x40,0x40,0x20,0x1c}, // V
	{0x70,0x7c,0x40,0x40,0x7c,0x40}, // W
	{0x70,0x7c,0x10,0x10,0x3c,0x00}, // X
	{0x1c,0x10,0x70,0x70,0x1c,0x00}, // Y
	{0x74,0x74,0x54,0x54,0x5c,0x00}, // Z
	{0xf0,0xfe,0x82,0x00,0x00,0x00}, // [
	{0x03,0x7c,0x70,0x00,0x00,0x00}, // "\"
	{0x82,0xfe,0xf0,0x00,0x00,0x00}, // ]
	{0x00,0x00,0x00,0x00,0x00,0x00}, // ^
	{0x40,0x40,0x40,0x40,0x00,0x00}, // _
	{0x00,0x00,0x00,0x00,0x00,0x00}, // `
	{0x70,0x7c,0x14,0x14,0x3c,0x00}, // a
	{0x7c,0x74,0x54,0x54,0x7c,0x00}, // b
	{0x70,0x7c,0x44,0x44,0x44,0x44}, // c
	{0x70,0x7c,0x44,0x44,0x48,0x70}, // d
	{0x70,0x7c,0x54,0x54,0x54,0x44}, // e
	{0x70,0x7c,0x14,0x14,0x14,0x04}, // f
	{0x70,0x7c,0x44,0x44,0x54,0x74}, // g
	{0x70,0x7c,0x10,0x10,0x7c,0x00}, // h
	{0x70,0x7c,0x00,0x00,0x00,0x00}, // i
	{0x60,0x40,0x40,0x40,0x7c,0x70}, // j
	{0x7c,0x70,0x10,0x1c,0x70,0x00}, // k
	{0x70,0x7c,0x40,0x40,0x40,0x60}, // l
	{0x70,0x7c,0x04,0x04,0x7c,0x04}, // m
	{0x70,0x7c,0x04,0x04,0x04,0x7c}, // n
	{0x70,0x7c,0x44,0x44,0x44,0x7c}, // o
	{0x70,0x7c,0x24,0x24,0x3c,0x00}, // p
	{0x7c,0x44,0x44,0x44,0x7c,0x00}, // q
	{0x7c,0x74,0x14,0x14,0x3c,0x00}, // r
	{0x5c,0x5c,0x54,0x54,0x74,0x00}, // s
	{0x04,0x04,0x7c,0x74,0x04,0x00}, // t
	{0x70,0x7c,0x40,0x40,0x40,0x7c}, // u
	{0x70,0x7c,0x40,0x40,0x20,0x1c}, // v
	{0x70,0x7c,0x40,0x40,0x7c,0x40}, // w
	{0x70,0x7c,0x10,0x10,0x3c,0x00}, // x
	{0x1c,0x10,0x70,0x70,0x1c,0x00}, // y
	{0x74,0x74,0x54,0x54,0x5c,0x00}, // z
	{0x00,0x00,0x00,0x00,0x00,0x00}, // {
	{0x00,0x00,0x00,0x00,0x00,0x00}, // |
	{0x00,0x00,0x00,0x00,0x00,0x00}, // }
	{0x00,0x00,0x00,0x00,0x00,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00}
};