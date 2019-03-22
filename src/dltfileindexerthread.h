#ifndef DLTFILEINDEXERTHREAD_H
#define DLTFILEINDEXERTHREAD_H

#include "dltfileindexer.h"
#include "dltmsgqueue.h"
#include <QThread>

class DltFileIndexerThread :public QThread
{
    Q_OBJECT
public:
    DltFileIndexerThread(DltFileIndexer *indexer,
                         QDltFilterList *filterList,
                         IndexSortType sortBy,
                         QVector<qint64> *indexFilterList,
                         QMultiMap<DltFileIndexerTimeKey,qint64> *indexFilterListTimeSorted,
                         QMultiMap<DltFileIndexerTimestampKey,qint64> *indexFilterListTimestampSorted,
                         QDltPluginManager *pluginManager,
                         QList<QDltPlugin*> *activeViewerPlugins,
                         bool silentMode);
    ~DltFileIndexerThread();
    void enqueueMessage(const QSharedPointer<QDltMsg> &msg, int index);
    void processMessage(QSharedPointer<QDltMsg> &msg, int index);
    void requestStop();

protected:
    void run();

private:
    DltFileIndexer *indexer;
    QDltFilterList *filterList;
    IndexSortType sortBy;

    QVector<qint64> *indexFilterList;
    QMultiMap<DltFileIndexerTimeKey,qint64> *indexFilterListTimeSorted;
    QMultiMap<DltFileIndexerTimestampKey,qint64> *indexFilterListTimestampSorted;

    QDltPluginManager *pluginManager;
    QList<QDltPlugin*> *activeViewerPlugins;
    bool silentMode;

    DltMsgQueue msgQueue;
};

#endif // DLTFILEINDEXERTHREAD_H
