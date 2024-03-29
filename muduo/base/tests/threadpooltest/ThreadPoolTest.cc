

#include <functional>   // std::bind
#include <stdio.h>

#include <gtest/gtest.h>

#include <muduo/base/ThreadPool.h>
#include <muduo/base/CountDownLatch.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Logging.h>

void print()
{
	printf("tid=%d\n", muduo::CurrentThread::tid());
}

void printString(const std::string& str)
{
	LOG_INFO << str;
	std::this_thread::sleep_for(std::chrono::microseconds(100 * 1000));

}

void test(int maxSize)
{
	LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
	muduo::ThreadPool pool("MainThreadPool");
	pool.setMaxQueueSize(maxSize);
	pool.start(5);

	LOG_WARN << "Adding";
	pool.run(print);
	pool.run(print);
	for (int i = 0; i < 100; ++i)
	{
		char buf[32];
		snprintf(buf, sizeof buf, "task %d", i);
		pool.run(std::bind(printString, std::string(buf)));
	}
	LOG_WARN << "Done";

	muduo::CountDownLatch latch(1);
	pool.run(std::bind(&muduo::CountDownLatch::countDown, &latch));
	latch.wait();
	pool.stop();
}

TEST(ThreadTestPool, Test)
{
	test(0);
	test(1);
	test(5);
	test(10);
	test(50);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

