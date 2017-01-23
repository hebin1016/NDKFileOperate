package com.example.ndkfileoperate;

import java.io.File;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;

public class MainActivity extends Activity {
	
	
	
	private String SD_CARD_PATH;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		SD_CARD_PATH = Environment.getExternalStorageDirectory().getAbsolutePath();
	}
	
	/**
	 * 拆分
	 * @param btn
	 */
	public void mDiff(View btn){		
		String path = SD_CARD_PATH +File.separatorChar+ "timg.jpeg";
		File file=new File(path);
		if(!file.exists()){
			Log.d("MainActivity", "文件不存在..");
		}
		String path_pattern = SD_CARD_PATH +File.separatorChar+ "timg_%d.jpeg";
		NDKFileUtils.diff(path, path_pattern, 3);
		Log.d("MainActivity", "拆分完毕..");
	}
	
	/**
	 * 合并
	 * @param btn
	 */
	public void mPatch(View btn){				
		String path_pattern = SD_CARD_PATH +File.separatorChar+ "timg_%d.jpeg";
		String merge_path = SD_CARD_PATH +File.separatorChar+ "timg_merge.jpeg";
		NDKFileUtils.patch(path_pattern, 3, merge_path);
		Log.d("MainActivity", "合并完毕..");
		
	}
	
}
