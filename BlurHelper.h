#pragma once
#include <vector>
#include <cmath>

class BlurHelper
{
public:
    static void GaussianAproximationBlur(std::vector<unsigned char>& scl, std::vector<unsigned char>& tcl, int w, int h, int r) {
        std::vector<unsigned char> bxs = BoxesForGaussApproximation(r, 3);
        BoxBlur(scl, tcl, w, h, (bxs[0] - 1) / 2);
        BoxBlur(tcl, scl, w, h, (bxs[1] - 1) / 2);
        BoxBlur(scl, tcl, w, h, (bxs[2] - 1) / 2);
    }

private:
    static void BoxBlurWidth(std::vector<unsigned char>& scl, std::vector<unsigned char>& tcl, int w, int h, int r) {
        float iarr = 1.0f / (r + r + 1);
        for (int i = 0; i < w; i++) {
            int ti = i, li = ti, ri = ti + r * w;
            int fv = scl[ti], lv = scl[ti + w * (h - 1)], val = (r + 1) * fv;
            for (int j = 0; j < r; j++) val += scl[ti + j * w];
            for (int j = 0; j <= r; j++) {
                val += scl[ri] - fv;
                tcl[ti] = std::round(val * iarr);
                ri += w;
                ti += w;
            }
            for (int j = r + 1; j < h - r; j++) {
                val += scl[ri] - scl[li];
                tcl[ti] = std::round(val * iarr);
                li += w;
                ri += w;
                ti += w;
            }
            for (int j = h - r; j < h; j++) {
                val += lv - scl[li];
                tcl[ti] = std::round(val * iarr);
                li += w;
                ti += w;
            }
        }
    }

    static void BoxBlurHeight(std::vector<unsigned char>& scl, std::vector<unsigned char>& tcl, int w, int h, int r) {
        float iarr = 1.0f / (r + r + 1);
        for (int i = 0; i < h; i++) {
            int ti = i * w, li = ti, ri = ti + r;
            int fv = scl[ti], lv = scl[ti + w - 1], val = (r + 1) * fv;
            for (int j = 0; j < r; j++) val += scl[ti + j];
            for (int j = 0; j <= r; j++) {
                val += scl[ri++] - fv;
                tcl[ti++] = std::round(val * iarr);
            }
            for (int j = r + 1; j < w - r; j++) {
                val += scl[ri++] - scl[li++];
                tcl[ti++] = std::round(val * iarr);
            }
            for (int j = w - r; j < w; j++) {
                val += lv - scl[li++];
                tcl[ti++] = std::round(val * iarr);
            }
        }
    }

    static void BoxBlur(std::vector<unsigned char>& scl, std::vector<unsigned char>& tcl, int w, int h, int r) {
        for (int i = 0; i < scl.size(); i++)
        {
            tcl[i] = scl[i];
        }
        BoxBlurHeight(tcl, scl, w, h, r);
        BoxBlurWidth(scl, tcl, w, h, r);
    }

    static std::vector<unsigned char> BoxesForGaussApproximation(double sigma, int n) {
        double wIdeal = std::sqrt((12 * sigma * sigma / n) + 1);
        int wl = static_cast<int>(wIdeal);
        if (wl % 2 == 0) wl--;

        int wu = wl + 2;

        double mIdeal = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
        int m = static_cast<int>(std::round(mIdeal));

        std::vector<unsigned char> sizes(n);
        for (int i = 0; i < n; i++) {
            sizes[i] = (i < m) ? wl : wu;
        }

        return sizes;
    }
};

