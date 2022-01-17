<script lang="ts">
	export let step;
</script>

<div center>
	<h1 text-8xl>Time-To-Market</h1>
	<p text-4xl class:visible={step > 0}><b>2 Month</b> - First working prototyp</p>
	<p text-4xl class:visible={step > 1}><b>5 Month</b> - Working with partners</p>
	<p text-4xl class:visible={step > 2}><b>12 Month</b> - Product Launch</p>
</div>

<style>
	p {
		opacity: 0;
		transition: opacity 0.3s ease;
	}

	h1,
	p {
		margin: 10px 0px;
	}

	p.visible {
		opacity: 1;
	}
</style>
