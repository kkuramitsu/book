int x=1; // 0x00000001
if (*(char*)&x) {
        /* little endian. memory image 01 00 00 00 */
}else{
        /* big endian. memory image 00 00 00 01 */
}

