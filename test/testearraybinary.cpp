#include "ArrayBinary.h"
#include <UnitTest++.h>

using namespace tightdb;

struct db_setup_binary {
	static ArrayBinary c;
};

ArrayBinary db_setup_binary::c;

TEST_FIXTURE(db_setup_binary, ArrayBinaryMultiEmpty) {
	c.Add("", 0);
	c.Add("", 0);
	c.Add("", 0);
	c.Add(NULL, 0);
	c.Add(NULL, 0);
	c.Add(NULL, 0);

	CHECK_EQUAL(6, c.Size());

	CHECK_EQUAL(0, c.GetLen(0));
	CHECK_EQUAL(0, c.GetLen(1));
	CHECK_EQUAL(0, c.GetLen(2));
	CHECK_EQUAL(0, c.GetLen(3));
	CHECK_EQUAL(0, c.GetLen(4));
	CHECK_EQUAL(0, c.GetLen(5));
}

TEST_FIXTURE(db_setup_binary, ArrayBinarySet) {
	c.Set(0, (void*)"hey", 4);

	CHECK_EQUAL(6, c.Size());

	CHECK_EQUAL("hey", (const char*)c.Get(0));
	CHECK_EQUAL(4, c.GetLen(0));
	CHECK_EQUAL(0, c.GetLen(1));
	CHECK_EQUAL(0, c.GetLen(2));
	CHECK_EQUAL(0, c.GetLen(3));
	CHECK_EQUAL(0, c.GetLen(4));
	CHECK_EQUAL(0, c.GetLen(5));
}

TEST_FIXTURE(db_setup_binary, ArrayBinaryAdd) {
	c.Clear();
	CHECK_EQUAL(0, c.Size());

	c.Add((void*)"abc", 4);
	CHECK_EQUAL("abc", (const char*)c.Get(0)); // single
	CHECK_EQUAL(4, c.GetLen(0));
	CHECK_EQUAL(1, c.Size());

	c.Add((void*)"defg", 5); //non-empty
	CHECK_EQUAL("abc", (const char*)c.Get(0));
	CHECK_EQUAL("defg", (const char*)c.Get(1));
	CHECK_EQUAL(4, c.GetLen(0));
	CHECK_EQUAL(5, c.GetLen(1));
	CHECK_EQUAL(2, c.Size());
}

TEST_FIXTURE(db_setup_binary, ArrayBinarySet2) {
	// {shrink, grow} x {first, middle, last, single}
	c.Clear();

	c.Add((void*)"abc", 4);
	c.Set(0, (void*)"de", 3); // shrink single
	CHECK_EQUAL("de", (const char*)c.Get(0));
	CHECK_EQUAL(1, c.Size());

	c.Set(0, (void*)"abcd", 5); // grow single
	CHECK_EQUAL("abcd", (const char*)c.Get(0));
	CHECK_EQUAL(1, c.Size());

	c.Add((void*)"efg", 4);
	CHECK_EQUAL("abcd", (const char*)c.Get(0));
	CHECK_EQUAL("efg", (const char*)c.Get(1));
	CHECK_EQUAL(2, c.Size());

	c.Set(1, (void*)"hi", 3); // shrink last
	CHECK_EQUAL("abcd", (const char*)c.Get(0));
	CHECK_EQUAL("hi", (const char*)c.Get(1));
	CHECK_EQUAL(2, c.Size());

	c.Set(1, (void*)"jklmno", 7); // grow last
	CHECK_EQUAL("abcd", (const char*)c.Get(0));
	CHECK_EQUAL("jklmno", (const char*)c.Get(1));
	CHECK_EQUAL(2, c.Size());

	c.Add((void*)"pq", 3);
	c.Set(1, (void*)"efghijkl", 9); // grow middle
	CHECK_EQUAL("abcd", (const char*)c.Get(0));
	CHECK_EQUAL("efghijkl", (const char*)c.Get(1));
	CHECK_EQUAL("pq", (const char*)c.Get(2));
	CHECK_EQUAL(3, c.Size());

	c.Set(1, (void*)"x", 2); // shrink middle
	CHECK_EQUAL("abcd", (const char*)c.Get(0));
	CHECK_EQUAL("x", (const char*)c.Get(1));
	CHECK_EQUAL("pq", (const char*)c.Get(2));
	CHECK_EQUAL(3, c.Size());

	c.Set(0, (void*)"qwertyuio", 10); // grow first
	CHECK_EQUAL("qwertyuio", (const char*)c.Get(0));
	CHECK_EQUAL("x", (const char*)c.Get(1));
	CHECK_EQUAL("pq", (const char*)c.Get(2));
	CHECK_EQUAL(3, c.Size());

	c.Set(0, (void*)"mno", 4); // shrink first
	CHECK_EQUAL("mno", (const char*)c.Get(0));
	CHECK_EQUAL("x", (const char*)c.Get(1));
	CHECK_EQUAL("pq", (const char*)c.Get(2));
	CHECK_EQUAL(3, c.Size());
}

TEST_FIXTURE(db_setup_binary, ArrayBinaryInsert) {
	c.Clear();

	c.Insert(0, (void*)"abc", 4); // single
	CHECK_EQUAL("abc", (const char*)c.Get(0));
	CHECK_EQUAL(1, c.Size());

	c.Insert(1, (void*)"d", 2); // end
	CHECK_EQUAL("abc", (const char*)c.Get(0));
	CHECK_EQUAL("d", (const char*)c.Get(1));
	CHECK_EQUAL(2, c.Size());

	c.Insert(2, (void*)"ef", 3); // end
	CHECK_EQUAL("abc", (const char*)c.Get(0));
	CHECK_EQUAL("d", (const char*)c.Get(1));
	CHECK_EQUAL("ef", (const char*)c.Get(2));
	CHECK_EQUAL(3, c.Size());

	c.Insert(1, (void*)"ghij", 5); // middle
	CHECK_EQUAL("abc", (const char*)c.Get(0));
	CHECK_EQUAL("ghij", (const char*)c.Get(1));
	CHECK_EQUAL("d", (const char*)c.Get(2));
	CHECK_EQUAL("ef", (const char*)c.Get(3));
	CHECK_EQUAL(4, c.Size());

	c.Insert(0, (void*)"klmno", 6); // first
	CHECK_EQUAL("klmno", (const char*)c.Get(0));
	CHECK_EQUAL("abc", (const char*)c.Get(1));
	CHECK_EQUAL("ghij", (const char*)c.Get(2));
	CHECK_EQUAL("d", (const char*)c.Get(3));
	CHECK_EQUAL("ef", (const char*)c.Get(4));
	CHECK_EQUAL(5, c.Size());
}

TEST_FIXTURE(db_setup_binary, ArrayBinaryDelete) {
	c.Clear();

	c.Add((void*)"a", 2);
	c.Add((void*)"bc", 3);
	c.Add((void*)"def", 4);
	c.Add((void*)"ghij", 5);
	c.Add((void*)"klmno", 6);

	c.Delete(0); // first
	CHECK_EQUAL("bc", (const char*)c.Get(0));
	CHECK_EQUAL("def", (const char*)c.Get(1));
	CHECK_EQUAL("ghij", (const char*)c.Get(2));
	CHECK_EQUAL("klmno", (const char*)c.Get(3));
	CHECK_EQUAL(4, c.Size());

	c.Delete(3); // last
	CHECK_EQUAL("bc", (const char*)c.Get(0));
	CHECK_EQUAL("def", (const char*)c.Get(1));
	CHECK_EQUAL("ghij", (const char*)c.Get(2));
	CHECK_EQUAL(3, c.Size());

	c.Delete(1); // middle
	CHECK_EQUAL("bc", (const char*)c.Get(0));
	CHECK_EQUAL("ghij", (const char*)c.Get(1));
	CHECK_EQUAL(2, c.Size());

	c.Delete(0); // single
	CHECK_EQUAL("ghij", (const char*)c.Get(0));
	CHECK_EQUAL(1, c.Size());

	c.Delete(0); // all
	CHECK_EQUAL(0, c.Size());
	CHECK(c.IsEmpty());
}

TEST_FIXTURE(db_setup_binary, ArrayBinary_Destroy) {
	// clean up (ALWAYS PUT THIS LAST)
	c.Destroy();
}
