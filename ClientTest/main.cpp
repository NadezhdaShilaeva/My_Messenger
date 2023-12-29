#include <QTest>
#include <QApplication>

#include "LoginServiceTest.h"
#include "ChatServiceTest.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;
    status |= QTest::qExec(new LoginServiceTest, argc, argv);
    status |= QTest::qExec(new ChatServiceTest, argc, argv);

    return status;
}
