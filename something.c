void getHist(Mat &src)
{
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	int b = Otsu(b_hist);
	int g = Otsu(g_hist);
	int r = Otsu(r_hist);
	printf("%d\n", b);
	printf("%d\n", g);
	printf("%d\n", r);
	/// Draw for each channel


	threshold(bgr_planes[0], bgr_planes[0], b, 255, THRESH_BINARY);
	threshold(bgr_planes[1], bgr_planes[1], g, 255, THRESH_BINARY);
	threshold(bgr_planes[2], bgr_planes[2], r, 255, THRESH_BINARY);
	merge(bgr_planes, src);
	namedWindow("src", WINDOW_NORMAL);
	imshow("src", src);
	rectangle(histImage, Point(bin_w*(b), 0), Point(bin_w*(b - 1), 400), Scalar(255, 0, 0));
	for (int i = 1; i < histSize; i++)
	{
		line(histImage,
			Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	waitKey(0);

}

float OtsuPart(Mat hist, int t)
{
	float avg1 = 1, avg2 = 1;
	int s1 = 0, s2 = 0;
	for (int i = 0; i < 256; i++)
	{
		int val = cvRound(hist.at<float>(i));

		if (i < t)
		{
			s1 += i*val;
			avg1 += val;
		}
		else
		{
			s2 += i*val;
			avg2 += val;
		}
	}
	float u1, u2;
	u1 = s1 / avg1;
	u2 = s2 / avg2;
	float sigma1 = 0, sigma2 = 0;
	for (int i = 0; i < 256; i++)
	{
		int val = cvRound(hist.at<float>(i));
		if (i < t)
		{
			sigma1 += (u1 - i)*(u1 - i)*val;
		}
		else
		{
			sigma2 += (u2 - i)*(u2 - i)*val;
		}
	}
	return sigma1 + sigma2;
}

int Otsu(Mat hist)
{
	float min = OtsuPart(hist, 0);
	int minindex = 256;
	//printf("min:%f", min);
	for (int i = 0; i < 255; i++)
	{
		float val = OtsuPart(hist, i);
		printf("val:%f\n", val);
		if (val - min < 0)
		{
			min = val;
			minindex = i;
		}
	}
	return minindex;
}