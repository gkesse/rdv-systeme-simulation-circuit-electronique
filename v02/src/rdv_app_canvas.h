#pragma once

#include "rdv_app_include.h"

class KtlQCanvasChunk;

class KtlQCanvas : public QObject
{
    Q_OBJECT

public:
    KtlQCanvas(QObject *parent = nullptr);
    KtlQCanvas(const int w, const int h);
    KtlQCanvas(QPixmap p, int h, int v, int tilewidth, int tileheight);
    ~KtlQCanvas() override;

    virtual void setTiles(QPixmap tiles, int h, int v, int tilewidth, int tileheight);
    virtual void retune(int chunksize, int maxclusters = 100);
    virtual void setChanged(const QRect &area);

    virtual void setAllChanged() { setChanged(m_size); }

private:
    void init(int w, int h, int chunksze = 16, int maxclust = 100);
    void init(const QRect &r, int chunksze = 16, int maxclust = 100);
    void initChunkSize(const QRect &s);

private:
    QPixmap offscr;
    int chunksize;
    int maxclusters;
    QRect m_size;
    QRect m_chunkSize;
    KtlQCanvasChunk *chunks;
    ushort *grid;
    ushort htiles;
    ushort vtiles;
    ushort tilew;
    ushort tileh;
    bool oneone;
    QPixmap pm;
    QTimer *update_timer;
    QColor bgcolor;
    bool debug_redraw_areas;
};
