# Traffic-Sign-Detection
利用hist.cpp丟入多張影像建立特徵資料庫，執行過後，可以透過批次檔一次建立多張影像資料庫<br>
特徵擷取方法為影像分為垂直切或是水平切，並算每份的平均值，因此每張圖會有自己的特徵值，之後執行find.cpp，丟入待測影像，結果便會輸出前五相似的道路號誌
