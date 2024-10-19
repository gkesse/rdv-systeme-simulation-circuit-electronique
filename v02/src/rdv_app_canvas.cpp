#include "rdv_app_canvas.h"
#include "rdv_app_canvas_chunk.h"

static int gcd(int a, int b)
{
    int r;
    while ((r = a % b))
    {
        a = b;
        b = r;
    }
    return b;
}

static int scm(int a, int b)
{
    int g = gcd(a, b);
    return a / g * b;
}

KtlQCanvas::KtlQCanvas(QObject *parent)
    : QObject(parent)
{
    init(0, 0);
}

KtlQCanvas::KtlQCanvas(const int w, const int h)
{
    init(w, h);
}

KtlQCanvas::KtlQCanvas(QPixmap p, int h, int v, int tilewidth, int tileheight)
{
    init(h * tilewidth, v * tileheight, scm(tilewidth, tileheight));
    setTiles(p, h, v, tilewidth, tileheight);
}

KtlQCanvas::~KtlQCanvas()
{
}

void KtlQCanvas::init(int w, int h, int chunksze, int mxclusters)
{
    init(QRect(0, 0, w, h), chunksze, mxclusters);
}

void KtlQCanvas::init(const QRect &r, int chunksze, int mxclusters)
{
    m_size = r;
    chunksize = chunksze;
    maxclusters = mxclusters;
    initChunkSize(r);
    chunks = new KtlQCanvasChunk[m_chunkSize.width() * m_chunkSize.height()];
    update_timer = nullptr;
    bgcolor = Qt::white;
    grid = nullptr;
    htiles = 0;
    vtiles = 0;
    debug_redraw_areas = false;
}

void KtlQCanvas::setTiles(QPixmap p, int h, int v, int tilewidth, int tileheight)
{
    if (!p.isNull() && (!tilewidth || !tileheight || p.width() % tilewidth != 0 || p.height() % tileheight != 0))
        return;

    htiles = h;
    vtiles = v;
    delete[] grid;
    pm = p;
    if (h && v && !p.isNull())
    {
        grid = new ushort[h * v];
        memset(grid, 0, h * v * sizeof(ushort));
        tilew = tilewidth;
        tileh = tileheight;
    }
    else
    {
        grid = nullptr;
    }
    if (h + v > 10)
    {
        int s = scm(tilewidth, tileheight);
        retune(s < 128 ? s : std::max(tilewidth, tileheight));
    }
    setAllChanged();
}

void KtlQCanvas::retune(int chunksze, int mxclusters)
{
}

void KtlQCanvas::setChanged(const QRect &area)
{
}
